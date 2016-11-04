<?php


function hf_library_info_views_default_views() {
	$view = new view();
	$view->name = 'library_information';
	$view->description = 'Displays Hours, Contact, and Location information.';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'Library Information';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Library Information';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['query']['options']['query_comment'] = FALSE;
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['pager']['options']['items_per_page'] = '1';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['style_plugin'] = 'default';
	$handler->display->display_options['row_plugin'] = 'fields';
	$handler->display->display_options['row_options']['default_field_elements'] = FALSE;
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['nid']['alter']['text'] = '<table>
	<tr>
	<td>Sunday</td><td>[field_branch_sunday]</td>
	</tr>
	<tr>
	<td>Monday</td><td>[field_branch_monday]</td>
	</tr>
	<tr>
	<td>Tuesday</td><td>[field_branch_tuesday]</td>
	</tr>
	<tr>
	<td>Wednesday</td><td>[field_branch_wednesday]</td>
	</tr>
	<tr>
	<td>Thursday</td><td>[field_branch_thursday]</td>
	</tr>
	<tr>
	<td>Friday</td><td>[field_branch_friday]</td>
	</tr>
	<tr>
	<td>Saturday</td><td>[field_branch_saturday]</td>
	</tr>
	</table>';
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	/* Sort criterion: Content: Title */
	$handler->display->display_options['sorts']['title']['id'] = 'title';
	$handler->display->display_options['sorts']['title']['table'] = 'node';
	$handler->display->display_options['sorts']['title']['field'] = 'title';
	/* Contextual filter: Content: Nid */
	$handler->display->display_options['arguments']['nid']['id'] = 'nid';
	$handler->display->display_options['arguments']['nid']['table'] = 'node';
	$handler->display->display_options['arguments']['nid']['field'] = 'nid';
	$handler->display->display_options['arguments']['nid']['default_action'] = 'default';
	$handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
	$handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
	$handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
	$handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'library_branch' => 'library_branch',
	);

	/* Display: Hours */
	$handler = $view->new_display('block', 'Hours', 'hours_block');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'Hours';
	$handler->display->display_options['defaults']['css_class'] = FALSE;
	$handler->display->display_options['css_class'] = 'branch-hours';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Content: Monday */
	$handler->display->display_options['fields']['field_branch_monday']['id'] = 'field_branch_monday';
	$handler->display->display_options['fields']['field_branch_monday']['table'] = 'field_data_field_branch_monday';
	$handler->display->display_options['fields']['field_branch_monday']['field'] = 'field_branch_monday';
	$handler->display->display_options['fields']['field_branch_monday']['label'] = '';
	$handler->display->display_options['fields']['field_branch_monday']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_monday']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_monday']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_monday']['element_wrapper_class'] = 'hours-monday';
	$handler->display->display_options['fields']['field_branch_monday']['element_default_classes'] = FALSE;
	/* Field: Content: Tuesday */
	$handler->display->display_options['fields']['field_branch_tuesday']['id'] = 'field_branch_tuesday';
	$handler->display->display_options['fields']['field_branch_tuesday']['table'] = 'field_data_field_branch_tuesday';
	$handler->display->display_options['fields']['field_branch_tuesday']['field'] = 'field_branch_tuesday';
	$handler->display->display_options['fields']['field_branch_tuesday']['label'] = '';
	$handler->display->display_options['fields']['field_branch_tuesday']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_tuesday']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_tuesday']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_tuesday']['element_wrapper_class'] = 'hours-tuesday';
	$handler->display->display_options['fields']['field_branch_tuesday']['element_default_classes'] = FALSE;
	/* Field: Content: Wednesday */
	$handler->display->display_options['fields']['field_branch_wednesday']['id'] = 'field_branch_wednesday';
	$handler->display->display_options['fields']['field_branch_wednesday']['table'] = 'field_data_field_branch_wednesday';
	$handler->display->display_options['fields']['field_branch_wednesday']['field'] = 'field_branch_wednesday';
	$handler->display->display_options['fields']['field_branch_wednesday']['label'] = '';
	$handler->display->display_options['fields']['field_branch_wednesday']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_wednesday']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_wednesday']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_wednesday']['element_wrapper_class'] = 'hours-wednesday';
	$handler->display->display_options['fields']['field_branch_wednesday']['element_default_classes'] = FALSE;
	/* Field: Content: Thursday */
	$handler->display->display_options['fields']['field_branch_thursday']['id'] = 'field_branch_thursday';
	$handler->display->display_options['fields']['field_branch_thursday']['table'] = 'field_data_field_branch_thursday';
	$handler->display->display_options['fields']['field_branch_thursday']['field'] = 'field_branch_thursday';
	$handler->display->display_options['fields']['field_branch_thursday']['label'] = '';
	$handler->display->display_options['fields']['field_branch_thursday']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_thursday']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_thursday']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_thursday']['element_wrapper_class'] = 'hours-thursday';
	$handler->display->display_options['fields']['field_branch_thursday']['element_default_classes'] = FALSE;
	/* Field: Content: Friday */
	$handler->display->display_options['fields']['field_branch_friday']['id'] = 'field_branch_friday';
	$handler->display->display_options['fields']['field_branch_friday']['table'] = 'field_data_field_branch_friday';
	$handler->display->display_options['fields']['field_branch_friday']['field'] = 'field_branch_friday';
	$handler->display->display_options['fields']['field_branch_friday']['label'] = '';
	$handler->display->display_options['fields']['field_branch_friday']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_friday']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_friday']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_friday']['element_wrapper_class'] = 'hours-friday';
	$handler->display->display_options['fields']['field_branch_friday']['element_default_classes'] = FALSE;
	/* Field: Content: Saturday */
	$handler->display->display_options['fields']['field_branch_saturday']['id'] = 'field_branch_saturday';
	$handler->display->display_options['fields']['field_branch_saturday']['table'] = 'field_data_field_branch_saturday';
	$handler->display->display_options['fields']['field_branch_saturday']['field'] = 'field_branch_saturday';
	$handler->display->display_options['fields']['field_branch_saturday']['label'] = '';
	$handler->display->display_options['fields']['field_branch_saturday']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_saturday']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_saturday']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_saturday']['element_wrapper_class'] = 'hours-saturday';
	$handler->display->display_options['fields']['field_branch_saturday']['element_default_classes'] = FALSE;
	/* Field: Content: Sunday */
	$handler->display->display_options['fields']['field_branch_sunday']['id'] = 'field_branch_sunday';
	$handler->display->display_options['fields']['field_branch_sunday']['table'] = 'field_data_field_branch_sunday';
	$handler->display->display_options['fields']['field_branch_sunday']['field'] = 'field_branch_sunday';
	$handler->display->display_options['fields']['field_branch_sunday']['label'] = '';
	$handler->display->display_options['fields']['field_branch_sunday']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_sunday']['element_label_colon'] = FALSE;
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['nid']['alter']['text'] = '<table>
	<tr>
	<td>Monday</td><td>[field_branch_monday]</td>
	</tr>
	<tr>
	<td>Tuesday</td><td>[field_branch_tuesday]</td>
	</tr>
	<tr>
	<td>Wednesday</td><td>[field_branch_wednesday]</td>
	</tr>
	<tr>
	<td>Thursday</td><td>[field_branch_thursday]</td>
	</tr>
	<tr>
	<td>Friday</td><td>[field_branch_friday]</td>
	</tr>
	<tr>
	<td>Saturday</td><td>[field_branch_saturday]</td>
	</tr>
	<tr>
	<td>Sunday</td><td>[field_branch_sunday]</td>
	</tr>
	</table>';
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	/* Field: Content: Location Notes */
	$handler->display->display_options['fields']['field_branch_location_notes']['id'] = 'field_branch_location_notes';
	$handler->display->display_options['fields']['field_branch_location_notes']['table'] = 'field_data_field_branch_location_notes';
	$handler->display->display_options['fields']['field_branch_location_notes']['field'] = 'field_branch_location_notes';
	$handler->display->display_options['fields']['field_branch_location_notes']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_location_notes']['element_wrapper_class'] = 'hours-notes';
	$handler->display->display_options['fields']['field_branch_location_notes']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['field_branch_location_notes']['hide_empty'] = TRUE;
	/* Field: Content: Link */
	$handler->display->display_options['fields']['view_node']['id'] = 'view_node';
	$handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['view_node']['field'] = 'view_node';
	$handler->display->display_options['fields']['view_node']['label'] = '';
	$handler->display->display_options['fields']['view_node']['alter']['nl2br'] = TRUE;
	$handler->display->display_options['fields']['view_node']['element_type'] = 'strong';
	$handler->display->display_options['fields']['view_node']['element_class'] = 'more-info-link';
	$handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['view_node']['text'] = '&raquo; More Information ';
	$handler->display->display_options['defaults']['filter_groups'] = FALSE;
	$handler->display->display_options['defaults']['filters'] = FALSE;
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'library_branch' => 'library_branch',
	);

	/* Display: Contact */
	$handler = $view->new_display('block', 'Contact', 'contact_block');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'Contact';
	$handler->display->display_options['defaults']['css_class'] = FALSE;
	$handler->display->display_options['css_class'] = 'branch-contact';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Content: Contact Persons */
	$handler->display->display_options['fields']['field_branch_contact']['id'] = 'field_branch_contact';
	$handler->display->display_options['fields']['field_branch_contact']['table'] = 'field_data_field_branch_contact';
	$handler->display->display_options['fields']['field_branch_contact']['field'] = 'field_branch_contact';
	$handler->display->display_options['fields']['field_branch_contact']['label'] = '';
	$handler->display->display_options['fields']['field_branch_contact']['alter']['text'] = '<span>Phone:</span><span>[field_branch_phone]</span>
	<span>Phone:</span><span>[field_Fa]</span>
	<span>Phone:</span><span>[field_branch_phone]</span>
	<span>Phone:</span><span>[field_branch_phone]</span>';
	$handler->display->display_options['fields']['field_branch_contact']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_contact']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_contact']['element_wrapper_class'] = 'contact-persons';
	$handler->display->display_options['fields']['field_branch_contact']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['field_branch_contact']['type'] = 'field_collection_fields';
	$handler->display->display_options['fields']['field_branch_contact']['settings'] = array(
	  'view_mode' => 'token',
	);
	$handler->display->display_options['fields']['field_branch_contact']['group_rows'] = FALSE;
	$handler->display->display_options['fields']['field_branch_contact']['delta_offset'] = '0';
	/* Field: Content: Link */
	$handler->display->display_options['fields']['view_node']['id'] = 'view_node';
	$handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['view_node']['field'] = 'view_node';
	$handler->display->display_options['fields']['view_node']['label'] = '';
	$handler->display->display_options['fields']['view_node']['element_type'] = 'strong';
	$handler->display->display_options['fields']['view_node']['element_class'] = 'more-info-link';
	$handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['view_node']['text'] = '&raquo; More Information ';

	/* Display: Location */
	$handler = $view->new_display('block', 'Location', 'location_block');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'Location';
	$handler->display->display_options['defaults']['css_class'] = FALSE;
	$handler->display->display_options['css_class'] = 'branch-location';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Content: Country */
	$handler->display->display_options['fields']['field_branch_country']['id'] = 'field_branch_country';
	$handler->display->display_options['fields']['field_branch_country']['table'] = 'field_data_field_branch_country';
	$handler->display->display_options['fields']['field_branch_country']['field'] = 'field_branch_country';
	$handler->display->display_options['fields']['field_branch_country']['label'] = '';
	$handler->display->display_options['fields']['field_branch_country']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_country']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_country']['element_default_classes'] = FALSE;
	/* Field: Content: State / Province */
	$handler->display->display_options['fields']['field_branch_state_province']['id'] = 'field_branch_state_province';
	$handler->display->display_options['fields']['field_branch_state_province']['table'] = 'field_data_field_branch_state_province';
	$handler->display->display_options['fields']['field_branch_state_province']['field'] = 'field_branch_state_province';
	$handler->display->display_options['fields']['field_branch_state_province']['label'] = '';
	$handler->display->display_options['fields']['field_branch_state_province']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_state_province']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_state_province']['element_default_classes'] = FALSE;
	/* Field: Content: City */
	$handler->display->display_options['fields']['field_branch_city']['id'] = 'field_branch_city';
	$handler->display->display_options['fields']['field_branch_city']['table'] = 'field_data_field_branch_city';
	$handler->display->display_options['fields']['field_branch_city']['field'] = 'field_branch_city';
	$handler->display->display_options['fields']['field_branch_city']['label'] = '';
	$handler->display->display_options['fields']['field_branch_city']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_city']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_city']['element_default_classes'] = FALSE;
	/* Field: Content: Street Address */
	$handler->display->display_options['fields']['field_branch_street_address']['id'] = 'field_branch_street_address';
	$handler->display->display_options['fields']['field_branch_street_address']['table'] = 'field_data_field_branch_street_address';
	$handler->display->display_options['fields']['field_branch_street_address']['field'] = 'field_branch_street_address';
	$handler->display->display_options['fields']['field_branch_street_address']['label'] = '';
	$handler->display->display_options['fields']['field_branch_street_address']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_street_address']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_street_address']['element_default_classes'] = FALSE;
	/* Field: Content: Postal Code / Zip */
	$handler->display->display_options['fields']['field_branch_postal_code_zip']['id'] = 'field_branch_postal_code_zip';
	$handler->display->display_options['fields']['field_branch_postal_code_zip']['table'] = 'field_data_field_branch_postal_code_zip';
	$handler->display->display_options['fields']['field_branch_postal_code_zip']['field'] = 'field_branch_postal_code_zip';
	$handler->display->display_options['fields']['field_branch_postal_code_zip']['label'] = '';
	$handler->display->display_options['fields']['field_branch_postal_code_zip']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_postal_code_zip']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_postal_code_zip']['element_default_classes'] = FALSE;
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['nid']['alter']['text'] = '<div class="location_area">
	<div class="location_level_one">[field_branch_street_address]</div>
	<div class="location_level_two">[field_branch_city]&nbsp; [field_branch_state_province]</div>
	<div class="location_level_three">[field_branch_country] [field_branch_postal_code_zip]</div>
	</div>';
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
	/* Field: Content: Geocode */
	$handler->display->display_options['fields']['field_branch_geocode']['id'] = 'field_branch_geocode';
	$handler->display->display_options['fields']['field_branch_geocode']['table'] = 'field_data_field_branch_geocode';
	$handler->display->display_options['fields']['field_branch_geocode']['field'] = 'field_branch_geocode';
	$handler->display->display_options['fields']['field_branch_geocode']['label'] = '';
	$handler->display->display_options['fields']['field_branch_geocode']['exclude'] = TRUE;
	$handler->display->display_options['fields']['field_branch_geocode']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_geocode']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_geocode']['element_wrapper_class'] = 'location-latitude';
	$handler->display->display_options['fields']['field_branch_geocode']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['field_branch_geocode']['click_sort_column'] = 'geom';
	$handler->display->display_options['fields']['field_branch_geocode']['settings'] = array(
	  'data' => 'full',
	);
	/* Field: Content: Geocode */
	$handler->display->display_options['fields']['field_branch_geocode_1']['id'] = 'field_branch_geocode_1';
	$handler->display->display_options['fields']['field_branch_geocode_1']['table'] = 'field_data_field_branch_geocode';
	$handler->display->display_options['fields']['field_branch_geocode_1']['field'] = 'field_branch_geocode';
	$handler->display->display_options['fields']['field_branch_geocode_1']['label'] = '';
	$handler->display->display_options['fields']['field_branch_geocode_1']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['field_branch_geocode_1']['alter']['text'] = '<div class="map">
	<a href="https://maps.google.ca/maps?q=[field_branch_geocode_1-lat],[field_branch_geocode_1-lon]&z=17" target="_blank">
	<img src="http://maps.google.com/maps/api/staticmap?size=500x200&markers=size:small|color:purple|[field_branch_geocode_1-lat],[field_branch_geocode_1-lon]&sensor=false" alt="" />
	</a>
	</div>';
	$handler->display->display_options['fields']['field_branch_geocode_1']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_geocode_1']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_geocode_1']['element_wrapper_class'] = 'location-longitude';
	$handler->display->display_options['fields']['field_branch_geocode_1']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['field_branch_geocode_1']['click_sort_column'] = 'geom';
	$handler->display->display_options['fields']['field_branch_geocode_1']['type'] = 'geofield_geojson';
	$handler->display->display_options['fields']['field_branch_geocode_1']['settings'] = array(
	  'data' => 'full',
	);
	/* Field: Content: Hours Notes */
	$handler->display->display_options['fields']['field_branch_notes']['id'] = 'field_branch_notes';
	$handler->display->display_options['fields']['field_branch_notes']['table'] = 'field_data_field_branch_notes';
	$handler->display->display_options['fields']['field_branch_notes']['field'] = 'field_branch_notes';
	$handler->display->display_options['fields']['field_branch_notes']['element_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_notes']['element_label_type'] = 'span';
	$handler->display->display_options['fields']['field_branch_notes']['element_wrapper_type'] = 'div';
	$handler->display->display_options['fields']['field_branch_notes']['element_wrapper_class'] = 'location-notes';
	$handler->display->display_options['fields']['field_branch_notes']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['field_branch_notes']['hide_empty'] = TRUE;
	/* Field: Content: Link */
	$handler->display->display_options['fields']['view_node']['id'] = 'view_node';
	$handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['view_node']['field'] = 'view_node';
	$handler->display->display_options['fields']['view_node']['label'] = '';
	$handler->display->display_options['fields']['view_node']['element_type'] = 'strong';
	$handler->display->display_options['fields']['view_node']['element_class'] = 'more-info-link';
	$handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['view_node']['text'] = '&raquo; More Information ';

	/* Display: Branch List */
	$handler = $view->new_display('block', 'Branch List', 'block_1');
	$handler->display->display_options['defaults']['css_class'] = FALSE;
	$handler->display->display_options['css_class'] = 'branch-list';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['pager'] = FALSE;
	$handler->display->display_options['pager']['type'] = 'none';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['defaults']['style_plugin'] = FALSE;
	$handler->display->display_options['style_plugin'] = 'default';
	$handler->display->display_options['style_options']['row_class_special'] = FALSE;
	$handler->display->display_options['defaults']['style_options'] = FALSE;
	$handler->display->display_options['defaults']['row_plugin'] = FALSE;
	$handler->display->display_options['row_plugin'] = 'fields';
	$handler->display->display_options['row_options']['default_field_elements'] = FALSE;
	$handler->display->display_options['defaults']['row_options'] = FALSE;
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['alter']['text'] = '<table>
	<tr>
	<td>Sunday</td><td>[field_branch_sunday]</td>
	</tr>
	<tr>
	<td>Monday</td><td>[field_branch_monday]</td>
	</tr>
	<tr>
	<td>Tuesday</td><td>[field_branch_tuesday]</td>
	</tr>
	<tr>
	<td>Wednesday</td><td>[field_branch_wednesday]</td>
	</tr>
	<tr>
	<td>Thursday</td><td>[field_branch_thursday]</td>
	</tr>
	<tr>
	<td>Friday</td><td>[field_branch_friday]</td>
	</tr>
	<tr>
	<td>Saturday</td><td>[field_branch_saturday]</td>
	</tr>
	</table>';
	$handler->display->display_options['fields']['nid']['element_type'] = 'div';
	$handler->display->display_options['fields']['nid']['element_class'] = 'nid';
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['element_type'] = 'div';
	$handler->display->display_options['fields']['title']['element_class'] = 'title';
	$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
	$handler->display->display_options['defaults']['sorts'] = FALSE;
	/* Sort criterion: Content: Title */
	$handler->display->display_options['sorts']['title']['id'] = 'title';
	$handler->display->display_options['sorts']['title']['table'] = 'node';
	$handler->display->display_options['sorts']['title']['field'] = 'title';

	/* Display: Day View Spud */
	$handler = $view->new_display('block', 'Day View Spud', 'block_2');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'Branch Calendar';
	$handler->display->display_options['defaults']['css_class'] = FALSE;
	$handler->display->display_options['css_class'] = 'day-view-spud';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Broken/missing handler */
	$handler->display->display_options['fields']['field_branch_day_view_spud']['id'] = 'field_branch_day_view_spud';
	$handler->display->display_options['fields']['field_branch_day_view_spud']['table'] = 'field_data_field_branch_day_view_spud';
	$handler->display->display_options['fields']['field_branch_day_view_spud']['field'] = 'field_branch_day_view_spud';
	$handler->display->display_options['fields']['field_branch_day_view_spud']['label'] = '';
	$handler->display->display_options['fields']['field_branch_day_view_spud']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_branch_day_view_spud']['element_default_classes'] = FALSE;
	$handler->display->display_options['defaults']['arguments'] = FALSE;
	/* Contextual filter: Content: Nid */
	$handler->display->display_options['arguments']['nid']['id'] = 'nid';
	$handler->display->display_options['arguments']['nid']['table'] = 'node';
	$handler->display->display_options['arguments']['nid']['field'] = 'nid';
	$handler->display->display_options['arguments']['nid']['default_action'] = 'default';
	$handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
	$handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
	$handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
	$handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

	/* Display: Library Select */
	$handler = $view->new_display('block', 'Library Select', 'branch_select_list');
	$handler->display->display_options['display_description'] = 'Populates our select list for Libraries on webforms Article, Item, and Ask a Librarian. ';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['pager'] = FALSE;
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['pager']['options']['items_per_page'] = '';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
	$handler->display->display_options['defaults']['arguments'] = FALSE;


	// add the view
	$views[$view->name] = $view;
	return $views;


}