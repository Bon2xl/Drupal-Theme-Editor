<?php
class day_in_history_database_field {

	function day_in_history_database_field($metadataRow) {
		$this->field = $metadataRow->Field;
		$this->type = $metadataRow->Type;
		$this->null = $metadataRow->Null;
		$this->key = $metadataRow->Key;
		$this->extra = $metadataRow->Extra;
	}

	function IsPrimaryKey(){
		return ($this->key === "PRI");
	}
	function ToString() {
		return  "$this->field \n";
	}
}
?>