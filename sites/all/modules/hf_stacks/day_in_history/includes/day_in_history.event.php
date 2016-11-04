<?php

require_once('day_in_history.model.php');

class day_in_history_event extends day_in_history_model {
	function day_in_history_event($id = null) {
		parent::day_in_history_model('day_in_history_events');

		if($id != null) {
			parent::load($id);
		}
	}

	public function getFormattedDate() {
	    if (intval($this['year']) > 0) {
	      return sprintf("%04d-%02d-%02d", intval($this['year']), intval($this['month']), intval($this['day']));
	    } else {
	      return (-intval($this['year']) + 1) . ' B.C. ' . sprintf("%02d-%02d", intval($this['month']), intval($this['day']));
	    }
	}
}

?>
