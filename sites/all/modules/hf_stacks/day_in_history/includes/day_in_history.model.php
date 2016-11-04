<?php

//This model assumes that the table has a primary key.
//This model assumes that the primary key is an integer.

include_once('day_in_history.databasefield.php');

class day_in_history_model extends ArrayObject {
	private static $tableDataCache;
	private static $tablePKCache;

	protected $tableName;	//The models table name
	protected $tableData;	//array of DatabaseFields
	protected $tablePK;		//The DatabaseField that represents the Primary Key.

	protected $id;			//The value of the primary key, can be null.
	protected $storedValues;//The current values of the model as they appear in the database. May go out of sync if the database is changed underneath the object. Thus direct changes to the db should be avoided.

	function day_in_history_model($tableName){
		parent::__construct(array());
		$this->tableName = $tableName;

		$this->loadTableMetaData();
		foreach ($this->tableData as $value) {
			$this["$value->field"] = null;
			//echo $value->ToString();
		}
	}

	private function loadTableMetaData() {
		//this makes the assumption that if the $tableDataCache is null so is the $tablePKCache
		if(is_null(day_in_history_model::$tableDataCache) || is_null(day_in_history_model::$tablePKCache)){
			day_in_history_model::$tableDataCache = array();
			day_in_history_model::$tablePKCache = array();
		}

		//this makes the assumption that if the $tableDataCache is populated so is the $tablePKCache
		if(array_key_exists($this->tableName, day_in_history_model::$tableDataCache)) {
			$this->tableData = day_in_history_model::$tableDataCache[$this->tableName];
			$this->tablePK = day_in_history_model::$tablePKCache[$this->tableName];
			return;
		}

		//no cached data available, fetch the tableData
		$results = db_query("desc $this->tableName");
		$this->tableData = array();

		foreach ($results as $metadataRow) {
			$database_field = new day_in_history_database_field($metadataRow);
			if($database_field->IsPrimaryKey()) {
				$this->tablePK = $database_field;
				day_in_history_model::$tablePKCache[$this->tableName] = $database_field;
			}

			$this->tableData[] = $database_field;
		}

		if(is_null(day_in_history_model::$tablePKCache[$this->tableName])){
			die("day_in_history.model requires that a models table has a primary key. Table $this->tableName does not.");
		}

		day_in_history_model::$tableDataCache[$this->tableName] = $this->tableData;
	}

	public function load($id){
    	$id = intval($id);
		if($id < 1){ // TODO: fix this
			die("day_in_history.model can only load a model using an integer id. Occurred while loading from table $this->tableName using $id.");
		}

		
		$query = "SELECT * FROM {{$this->tableName}} WHERE event_id = $id";
		$results = db_query($query);
		// error_log("results" . print_r($results->fetchAssoc(), TRUE));
		// $results = db_query($this->tableName)
		//            ->condition($this->tablePK->field, array($id))
		//            ->execute();
	    if (!$results) {
	      die(db_error());
	    }

    	$result_array = $results->fetchAssoc();
    	$this->id = $id;
    	$this->storedValues = $result_array;
		$this->exchangeArray($result_array);
	}

	public function save(){
		if(is_null($this->id)){
			$this->insert();
		}
		else {
			$this->update();
		}
	}

	private function insert(){
		$fields = array();
		$values = array();
		foreach ($this->tableData as $field) {
			if($field->IsPrimaryKey()){
				continue;
			}

			$value = $this["$field->field"];
			if($field->field == "created"){
				$fields[] = $field->field;
				$values[] = "NOW()";
			} else if(isset($value)){
				$fields[] = $field->field;
				$values[] = $this->db_prep_value($field, $this["$field->field"]);
			}
		}



		$query = "INSERT INTO {{$this->tableName}} (". implode(",",$fields) .") VALUES (". implode(",",$values) .")";
		//echo $query. "\n";
		db_query($query);
		if(!$query){
			echo "Insert statement failed \n";
			return;
		}

		$this->id = db_query("SELECT 1", array(), array('return' => Database::RETURN_INSERT_ID));

//		$this->id = db_last_insert_id('table', 'id'); // these parameters aren't used in mysql
		$this->storedValues = $this->getArrayCopy();
	}

	private function update(){
		$changes = array();
		$hasUpdates = false;

		foreach ($this->tableData as $field) {
			if($field->IsPrimaryKey()){
				continue;
			}

			if($field->field == "modified") {
				$changes[] = "$field->field = NOW()";
				continue;
			}

			$value = $this["$field->field"];
			if($this->storedValues[$field->field] !== $value) {
				$changes[] = "$field->field = " . $this->db_prep_value($field, $this["$field->field"]);
				$hasUpdates = true;

			}
		}

		if(!$hasUpdates) {
			return;
		}

		$query = "UPDATE {{$this->tableName}} SET ". implode(",", $changes) ." WHERE {$this->tablePK->field} = $this->id";
		//echo $query. "\n";
		db_query($query);

		if(!$query){
			echo "Update statement failed \n";
			return;
		}
	}

	public function delete() {
		if(!$this->id){
			echo 'Warning: you cannot delete a model that has no associated id';
		}

		$query = "Delete From {{$this->tableName}} WHERE item_id = $this->id";
		db_query($query);

		if(!$query){
			echo "Delete statement failed \n";
			return;
		}
	}

	protected function db_prep_value($field, $value) {
		$value = trim($value);
		if(strncasecmp('varchar', $field->type, 7) === 0 || strcasecmp('text', $field->type) === 0){
			return '\'' . ($value). '\'';
		}
		elseif(strncasecmp('int', $field->type, 3) === 0){
			return intval($value);
		}
		elseif(strncasecmp('decimal', $field->type, 7) === 0) {
			return is_numeric($value) && !preg_match('/x/i', $value) ? $value : '0'; //borrowed from _db_query_callback in drupal 6.
		}
		else {
			return $value;
		}
	}
}

?>
