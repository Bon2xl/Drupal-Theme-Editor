<?php
/**
 * Connector Class for Searching on EBSCO EDS Server
 */

class EDSSearch {

  /**
   * Error codes defined by EDS API
   */
  const EDS_UNKNOWN_PARAMETER              = 100;
  const EDS_INCORRECT_PARAMETER_FORMAT     = 101;
  const EDS_INVALID_PARAMETER_INDEX        = 102;
  const EDS_MISSING_PARAMETER              = 103;
  const EDS_AUTH_TOKEN_INVALID             = 104;
  const EDS_INCORRECT_ARGUMENTS_NUMBER     = 105;
  const EDS_UNKNOWN_ERROR                  = 106;
  const EDS_AUTH_TOKEN_MISSING             = 107;
  const EDS_SESSION_TOKEN_MISSING          = 108;
  const EDS_SESSION_TOKEN_INVALID          = 109;
  const EDS_INVALID_RECORD_FORMAT          = 110;
  const EDS_UNKNOWN_ACTION                 = 111;
  const EDS_INVALID_ARGUMENT_VALUE         = 112;
  const EDS_CREATE_SESSION_ERROR           = 113;
  const EDS_REQUIRED_DATA_MISSING          = 114;
  const EDS_TRANSACTION_LOGGING_ERROR      = 115;
  const EDS_DUPLICATE_PARAMETER            = 116;
  const EDS_UNABLE_TO_AUTHENTICATE         = 117;
  const EDS_SEARCH_ERROR                   = 118;
  const EDS_INVALID_PAGE_SIZE              = 119;
  const EDS_SESSION_SAVE_ERROR             = 120;
  const EDS_SESSION_ENDING_ERROR           = 121;
  const EDS_CACHING_RESULTSET_ERROR        = 122;
  const EDS_INVALID_EXPANDER_ERROR         = 123;
  const EDS_INVALID_SEARCH_MODE_ERROR      = 124;
  const EDS_INVALID_LIMITER_ERROR          = 125;
  const EDS_INVALID_LIMITER_VALUE_ERROR    = 126;
  const EDS_UNSUPPORTED_PROFILE_ERROR      = 127;
  const EDS_PROFILE_NOT_SUPPORTED_ERROR    = 128;
  const EDS_INVALID_CONTENT_PROVIDER_ERROR = 129;
  const EDS_INVALID_SOURCE_TYPE_ERROR      = 130;
  const EDS_XSLT_ERROR                     = 131;
  const EDS_RECORD_NOT_FOUND_ERROR         = 132;
  const EDS_SIMULTANEOUS_USER_LIMIT_ERROR  = 133;
  const EDS_NO_GUEST_ACCESS_ERROR          = 134;
  const EDS_DBID_NOT_IN_PROFILE_ERROR      = 135;
  const EDS_INVALID_SEARCH_VIEW_ERROR      = 136;
  const EDS_RETRIEVING_FULL_TEXT_ERROR     = 137;

  /**
   * HTTP status codes constants
   * http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
   */
  const HTTP_OK                    = 200;
  const HTTP_BAD_REQUEST           = 400;
  const HTTP_NOT_FOUND             = 404;
  const HTTP_INTERNAL_SERVER_ERROR = 500;

  // private variables
  //private static $END_POINT = "https://eds-api.ebscohost.com/edsapi/rest";
  private static $AUTH_END_POINT = "https://eds-api.ebscohost.com/Authservice/rest";
  //private static $USER_ID = "ns248783main";
  //private static $PASSWORD = "4plufngfqu";
  //private static $PROFILE = "edsapi";
  //private static $ORG_ID = "hybrid";
  private static $GUEST = "y";

  // public variables
  public $hits;
  public $search_time;
  public $search_url;
  public $facet_source_type;
  public $facet_subject;
  public $facet_language;
  public $facet_library_location;
  public $url_args;
  public $search_results;
  public $search_starter;
  public $sid;
  public $facets;


  /**
   * Constructor to set up the EDSConnector class
   */
  function __construct() {

  }

  /**
   *
   ****************************
   * QUERY BUILDING FUNCTIONS *
   ****************************
   *
   */

  function query($facets){
    $page_current = 1;

    //Get the url query string
    $url_args = $this->build_search_query($facets);
    $this->url_args = $url_args;
    $this->search_url = $url_args;

    //$raw_results = $this->execute_query();
    //$raw_results = $raw_results->buildSearch($raw_results);

    if (isset($facets['ff'])) {
      $ff = $facets['ff'][0];
    } else {
      $ff = "";
    }

    if (isset($facets['searchfield'])) {
      $searchfield = $facets['searchfield'];
    } else {
      $searchfield = "";
    }

    $search_query = $this->execute_query($ff,$searchfield);
    $raw_results = $this->buildSearch($search_query);
    $facets_query = $this->buildFacets($search_query);
    $this->raw_facets = $facets_query;

    //Set object properties
    $this->hits = $raw_results['recordCount'];
    $this->results_per_page = count($raw_results['records']);
    if (isset($_REQUEST['pagenumber'])) {
      $this->pagenumber = intval($_REQUEST['pagenumber']);
    } else {
      $this->pagenumber = $page_current;
    }

    if (isset($raw_results->SearchTime)) {
      $this->search_time = $raw_results->SearchTime;
    } else {
      $this->search_time = '';
    }

    //Facets can come back empty so check them before assignment
    if (isset($facets['ff'])) {
      $this->facets = $facets['ff'];
    }
    $this->search_results = $raw_results['records'];
    $this->search_starter = $raw_results['starter'];
  }

  function build_search_query($filter_array){
    $url_args = "?";

    //Turn the array into a url argument string
    if ($filter_array) {
      foreach($filter_array as $key => $data){
        if($this->is_multivalue_filter($key)){
          foreach($data as $key2 => $data2){
            $url_args .= $key . '[]=' . $data2 . '&';
          }
        } else {
          $url_args .= $key . '=' . $data . '&';
        }
      }
    }

    $url_args = substr($url_args, 0, -1);
    return $url_args;
  }

  function add_to_url($filter, $value){
    //If you are adding a new filter you will want to make you reset the pagination
    //You don't want to add a new search filter and be on page 3 so if you aren't adding
    //the page filter make sure that it is removed to go to page 1.
    if($filter != 'pagenumber'){
      if($result = $this->remove_from_url('pagenumber')){
        $this->url_args = $result;
      }
    }
    //Check to see if the filter passed is a multivalue filter
    if(!$this->is_multivalue_filter($filter)){
      //Check if the filter is already in the url
      if($new_args = $this->remove_from_url($filter)){
        return $new_args . "&$filter" . "=$value";
      } else {
        return $this->url_args . "&$filter" . "=$value";
      }
    } else {
      //Multi value filters simply get added
      return $this->url_args . "&$filter" . "[]=$value";
    }
  }

  function remove_from_url($filter, $value=NULL){
    $url_args = $this->url_args;
    //Explode args into array for enumerating
    $exploded = array();
    parse_str(substr($url_args, 1), $exploded);
    //Parse url depending on multi value or not
    if($this->is_multivalue_filter($filter)){
      foreach($exploded as $key => $data){
        if($key == $filter){
          foreach($data as $key2 => $data2){
            if($data2 == $value){
              unset($exploded[$key][$key2]);
              return $this->build_search_query($exploded);
            }
          }
        }
      }
      return FALSE;
    } else {
      //Single Value only need to find matching key
      foreach($exploded as $key => $data){
        if($key == $filter){
          unset($exploded[$key]);
          return $this->build_search_query($exploded);
        }
      }
      return FALSE;
    }
  }

  function is_multivalue_filter($param){
    $multi_value_filters = array('mediatype', 'mm', 'facetfilter', 'ff');
    if(in_array($param, $multi_value_filters) == false){
      return FALSE;
    } else {
      return TRUE;
    }
  }

  function set_url_filter($filter, $value){
    $new_args = $this->add_to_url($filter, $value);
    $this->url_args = $new_args;
    $this->search_url = $this->BASE_URL . $new_args;
    return $new_args;
  }

  function unset_url_filter($filter, $value=NULL){
    $new_args = $this->remove_from_url($filter, $value);
    $this->url_args = $new_args;
    $this->search_url = $this->BASE_URL . $new_args;
    return $new_args;
  }

  // This function calls the Search method with the user’s query
  public function execute_query($facetset,$searchfield) {
    try {
      $END_POINT = variable_get('stacks_eds_server');
      $USER_ID = variable_get('stacks_eds_user','');
      $PASSWORD = variable_get('stacks_eds_pass','');
      $PROFILE = variable_get('stacks_eds_profile','');
      $ORG_ID = variable_get('stacks_eds_org','');

      $url = $END_POINT . '/Search';

      if (isset($_REQUEST['ff'])) {
        $ff = $_REQUEST['ff'];
      } else {
        $ff = "";
      }

      // Build  the arguments for the Search API method
      $query = str_replace('"','',$_REQUEST['query']);
      // check to see if this is a "research starter"
      if ($facetset == "ContentProvider:Research Starters") {
        $search = array(
          'query' => $query,
          'ff'    => array($facetset),
        );
      } else {
        $search = array(
          'query' => $query,
          'ff'    => $ff,
        );
      }


      //Set search parameters for the Search API method
      if ($facetset == "ContentProvider:Research Starters") {
        $start = 1;
        $limit = 1;
        $sortBy = isset($_REQUEST['sortorder']) ? $_REQUEST['sortorder'] : 'relevance';
        $amount = isset($_REQUEST['amount']) ? $_REQUEST['amount'] : 'detailed';
        $from_date = isset($_REQUEST['from_date']) ? $_REQUEST['from_date'] : '';
        $to_date = isset($_REQUEST['to_date']) ? $_REQUEST['to_date'] : '';
        $mode = 'all';
      } else {
        $start = isset($_REQUEST['pagenumber']) ? $_REQUEST['pagenumber'] : 1;
        $start = intval($start);
        $limit = isset($_REQUEST['resultsperpage']) ? $_REQUEST['resultsperpage'] : 10;
        $sortBy = isset($_REQUEST['sortorder']) ? $_REQUEST['sortorder'] : 'relevance';
        $amount = isset($_REQUEST['amount']) ? $_REQUEST['amount'] : 'detailed';
        $from_date = isset($_REQUEST['from_date']) ? $_REQUEST['from_date'] : '';
        $to_date = isset($_REQUEST['to_date']) ? $_REQUEST['to_date'] : '';
        $mode = 'all';
      }

      $query = array();

      // Basic search
      if(!empty($search['query'])) {
        // escaping as needed
        $term = urldecode($search['query']);
        $term = str_replace('"', '', $term); // Temporary
        $term = str_replace(',',"\,",$term);
        $term = str_replace(':', '\:', $term);
        $term = str_replace('(', '\(', $term);
        $term = str_replace(')', '\)', $term);
        $type = $search['ff'];
        // Transform a Search type into an EBSCO search field code
        $tag = $this->fieldCodeSelect($type);
        $query_str = $term;

        if (!empty($searchfield)) {
          $query_str = $searchfield.":".$query_str;
        }

        $query["query"] = $query_str;
      } else {
        $results = array();
        return $results;
      }

      // Date Filtering
      if ((!empty($from_date)) && (!empty($to_date))) {
        $date_from = new DateTime($from_date);
        $date_from = $date_from->format('Y-m');
        $date_to = new DateTime($to_date);
        $date_to = $date_to->format('Y-m');

        $dates = array (
          'limiter' => 'DT1:'.$date_from.'/'.$date_to
        );
      } else {
        $dates = array();
      }

      // EDS Expanders
      $expanders = array();
      $stacks_search_eds_expander_thesaurus = variable_get('stacks_search_eds_expander_thesaurus');
      $stacks_search_eds_expander_fulltext = variable_get('stacks_search_eds_expander_fulltext');
      $stacks_search_eds_expander_precision = variable_get('stacks_search_eds_expander_precision');
      if (isset($stacks_search_eds_expander_thesaurus)) {
        $expanders[] = 'thesaurus';
      }
      if (isset($stacks_search_eds_expander_fulltext)) {
        $expanders[] = 'fulltext';
      }
      if (isset($stacks_search_eds_expander_precision)) {
        $expanders[] = 'relatedsubjects';
      }
      $expanders_string = implode(',', $expanders);

      // EDS Limites
      $limiters = array();
      $stacks_search_eds_limiter_ft = variable_get('stacks_search_eds_limiter_ft');
      $stacks_search_eds_limiter_fr = variable_get('stacks_search_eds_limiter_fr');
      $stacks_search_eds_limiter_rv = variable_get('stacks_search_eds_limiter_rv');
      $stacks_search_eds_limiter_ft1 = variable_get('stacks_search_eds_limiter_ft1');
      $stacks_search_eds_limiter_fc = variable_get('stacks_search_eds_limiter_fc');
      if (isset($stacks_search_eds_limiter_ft)) {
        $limiters[] = 'FT:y';
      }
      if (isset($stacks_search_eds_limiter_fr)) {
        $limiters[] = 'FR:y';
      }
      if (isset($stacks_search_eds_limiter_rv)) {
        $limiters[] = 'RV:y';
      }
      if (isset($stacks_search_eds_limiter_ft1)) {
        $limiters[] = 'FT1:y';
      }
      if (isset($stacks_search_eds_limiter_fc)) {
        $limiters[] = 'FC:y';
      }
      $limiters_string = implode(',', $limiters);

      // Add the HTTP query params
      $params = array(
        'sort'           => $sortBy,
        'searchmode'     => $mode,
        'view'           => $amount,
        'includefacets'  => 'y',
        'resultsperpage' => $limit,
        'pagenumber'     => $start,
        'highlight'      => 'y',
        'expander'       => $expanders_string,
        'limiter'        => $limiters_string,
        'relatedcontent' => 'rs',
      );

      $facet_terms = $search['ff'];

      if (!empty($facet_terms)) {
        $facetstring = "";
        foreach ($facet_terms as $facet) {
          $facetstring .= ','.$facet;
        }
        $facets = array (
          'facetfilter'    => '1'.$facetstring
        );
      } else {
        $facets = array();
      }

      $params = array_merge($params, $query, $facets, $dates);

      $authenticationToken = variable_get('hf_stacks_search_eds_authenticationToken');
      $sessionToken = variable_get('hf_stacks_search_eds_sessionToken');

      $headers = array(
        'x-authenticationToken: ' . $authenticationToken,
        'x-sessionToken: ' . $sessionToken
      );

      $response = '';
      $response = $this->sendHTTPRequest($url, $params, $headers);
      //$response = $this->buildSearch($response);

      return $response;

    } catch(Exception $e) {
      $result = array(
        'error' => $e->getMessage()
      );
      return $result;
    }
  }

  // This function calls the Search method with the user’s query
  public function execute_single($an, $db) {
    try{
      $END_POINT = variable_get('stacks_eds_server');
      $USER_ID = variable_get('stacks_eds_user','');
      $PASSWORD = variable_get('stacks_eds_pass','');
      $PROFILE = variable_get('stacks_eds_profile','');
      $ORG_ID = variable_get('stacks_eds_org','');

      $url = $END_POINT . '/Retrieve';

      $authenticationToken = variable_get('hf_stacks_search_eds_authenticationToken');
      $sessionToken = variable_get('hf_stacks_search_eds_sessionToken');

      $headers = array(
        'x-authenticationToken: ' . $authenticationToken,
        'x-sessionToken: ' . $sessionToken
      );

      $params = array(
        'an'        => $an,
        'dbid'      => $db
      );

      $headers = array(
        'x-authenticationToken: ' . $authenticationToken,
        'x-sessionToken: ' . $sessionToken
      );

      $response="";

      $response = $this->sendHTTPRequest($url, $params, $headers);
      $response = $this->buildSingle($response);

      return $response;
    } catch(Exception $e) {
      $result = array(
        'error' => $e->getMessage()
      );
      return $result;
    }
  }

  // This function uses the Retrieve XML response to create an array of the record in the detailed record page
  private function buildSingle($response) {
    $record = $response->Record;

    if ($record) {
      $record = $record[0]; // there is only one record
    }

    $result = array();
    $result['AccessLevel'] = $record->Header -> AccessLevel?(string)$record->Header -> AccessLevel:'';
    $result['pubType'] = $record -> Header-> PubType? (string)$record -> Header-> PubType:'';
    $result['PubTypeId']= $record->Header->PubTypeId? (string) $record->Header->PubTypeId:'';
    $result['DbId'] = $record->Header->DbId ? (string) $record->Header->DbId : '';
    $result['DbLabel'] = $record->Header->DbLabel ? (string) $record->Header->DbLabel:'';
    $result['An'] = $record->Header->An ? (string) $record->Header->An : '';
    $result['PLink'] = $record->PLink ? (string) $record->PLink : '';
    $result['pdflink'] = $record->FullText->Links ? (string) $record->FullText->Links->Link->Url : '';
    $result['PDF'] = $record->FullText->Links ? (string) $record->FullText->Links->Link->Type : '';
    $result['HTML'] = $record->FullText->Text->Availability? (string) $record->FullText->Text->Availability : '';
    $value = $record->FullText->Text->Value ? (string) $record->FullText->Text->Value : '';
    $result['htmllink'] = $this->toHTML($value,$group = '');
    if (!empty($record->ImageInfo->CoverArt)) {
      foreach ($record->ImageInfo->CoverArt as $image) {
        $size = (string) $image->Size;
        $target = (string) $image->Target;
        $result['ImageInfo'][$size] = $target;
      }
    } else {
      $result['ImageInfo'] = '';
    }
    $result['FullText'] = $record->FullText ? (string) $record->FullText : '';

    if ($record->CustomLinks) {
      $result['CustomLinks'] = array();
      foreach ($record->CustomLinks->CustomLink as $customLink) {
        $category = $customLink->Category ? (string) $customLink->Category : '';
        $icon = $customLink->Icon ? (string) $customLink->Icon : '';
        $mouseOverText = $customLink->MouseOverText ? (string) $customLink->MouseOverText : '';
        $name = $customLink->Name ? (string) $customLink->Name : '';
        $text = $customLink->Text ? (string) $customLink->Text : '';
        $url = $customLink->Url ? (string) $customLink->Url : '';
        $result['CustomLinks'][] = array(
          'Category'      => $category,
          'Icon'          => $icon,
          'MouseOverText' => $mouseOverText,
          'Name'          => $name,
          'Text'          => $text,
          'Url'           => $url
        );
      }
    }

    if($record->Items) {
      $result['Items'] = array();
      foreach ($record->Items->Item as $item) {
        $label = $item->Label ? (string) $item->Label : '';
        $group = $item->Group ? (string) $item->Group : '';
        $data = $item->Data ? (string) $item->Data : '';
        $result['Items'][] = array(
          'Label' => $label,
          'Group' => $group,
          'Data'  => $this->toHTML($data, $group)
        );
      }
    }

    if($record->RecordInfo->BibRecord->BibRelationships->IsPartOfRelationships->IsPartOf->BibEntity->Identifiers->Identifier) {
      $result['RecordInfo'] = array();
      foreach ($record->RecordInfo->BibRecord->BibRelationships->IsPartOfRelationships->IsPartOf->BibEntity->Identifiers->Identifier as $identifier) {
        $type = $identifier->Type ? (string) $identifier->Type : '';
        $value = $identifier->Value ? (string) $identifier->Value : '';
        $result['RecordInfo'][] = array(
          'Type' => $type,
          'Value' => $value
        );
      }
    }

    if($record->RecordInfo->BibRecord->BibEntity->Identifiers->Identifier) {
      $result['Identifier'] = array();
      foreach ($record->RecordInfo->BibRecord->BibEntity->Identifiers->Identifier as $identifier) {
        $type = $identifier->Type ? (string) $identifier->Type : '';
        $value = $identifier->Value ? (string) $identifier->Value : '';
        $result['Identifier'][] = array(
          'Type' => $type,
          'Value' => $value
        );
      }
    }

    if($record->RecordInfo->BibRecord->BibEntity->Languages->Language) {
      $result['Language'] = array();
      foreach ($record->RecordInfo->BibRecord->BibEntity->Languages->Language as $language) {
        $text = $language->Text ? (string) $language->Text : '';
        $result['Language'][] = array(
          'Text' => $text
        );
      }
    }

    if($record->RecordInfo->BibRecord->BibEntity->PhysicalDescription->Pagination) {
      $result['Pagination'] = array();
      foreach ($record->RecordInfo->BibRecord->BibEntity->PhysicalDescription->Pagination as $pagination) {
        $pagecount = $pagination->PageCount ? (string) $pagination->PageCount : '';
        $result['Pagination'][] = array(
          'PageCount' => $pagecount
        );
      }
    }

    return $result;
  }

  // This function is used to actually send the HTTP request and fetch the XML response from the API server
  protected function sendHTTPRequest($url, $params = null, $headers = null, $method = 'GET') {
    // Create a cURL instance
    $ch = curl_init();

    // Set the cURL options
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 5);
    curl_setopt($ch, CURLOPT_TIMEOUT, 10);
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
    //curl_setopt($ch, CURLOPT_STDERR, $log);  // for debugging cURL

    // Speeds up call
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
    curl_setopt($ch, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_setopt($ch, CURLOPT_USERAGENT, 'Mozilla/5.001 (windows; U; NT4.0; en-US; rv:1.0) Gecko/25250101');

    // Set the query parameters and the url
    if (empty($params)) {
      // Only Info request has empty parameters
      curl_setopt($ch, CURLOPT_URL, $url);
    } else {
      if ($method == 'GET') {
        // GET method
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'GET');

        $query = http_build_query($params);
        // replace query params like facet[0]=value with facet=value
        $query = preg_replace('/%5B(?:[0-9]|[1-9][0-9]+)%5D=/', '=', $query);
        $url .= '?' . $query;
        curl_setopt($ch, CURLOPT_URL, $url);
      } else {
        // POST method
        // Add the HTTP query params
        $params = '<SearchRequestMessage xmlns="http://epnet.com/webservices/EbscoApi/Contracts" xmlns:i="http://www.w3.org/2001/XMLSchema-instance">
            <SearchCriteria>
              <Queries>
                <Query>
                  <Term>Apple</Term>
                </Query>
              </Queries>
              <SearchMode>all</SearchMode>
              <IncludeFacets>y</IncludeFacets>
              <Expanders>
                <Id>fulltext</Id>
              </Expanders>
              <Sort>relevance</Sort>
            </SearchCriteria>
            <RetrievalCriteria>
              <View>detailed</View>
              <ResultsPerPage>2</ResultsPerPage>
              <PageNumber>2</PageNumber>
              <Highlight>y</Highlight>
            </RetrievalCriteria>
          </SearchRequestMessage> ';

        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_POSTFIELDS, $params);
      }
    }

    // Set the header
    if (!empty($headers)) {
      curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
    }

    // Send the request
    $response = curl_exec($ch);
    $response = $this->errorHandling($ch,$response);

    return $response;
  }

  // This function uses the Search XML response to create an array that stores the search results data
  private function buildSearch($response) {
    $hits = (integer) $response->SearchResult->Statistics->TotalHits;

    $records = array();
    $starter = array();

    if ($hits > 0) {
      $records = $this->buildRecords($response);
      $starter = $this->buildStarter($response);
    }

    $results = array(
      'recordCount' => $hits,
      'records'     => $records,
      'starter'    => $starter,
    );

    return $results;
  }

  // This function uses the Search XML response to create an array of the records in the results page
  private function buildRecords($response) {
    $results = array();

    $records = $response->SearchResult->Data->Records->Record;

    foreach ($records as $record) {
      $result = array();
      $result['pubType'] = $record -> Header-> PubType?(string)$record ->Header-> PubType:'';
      $result['PubTypeId']= $record->Header->PubTypeId? (string) $record->Header->PubTypeId:'';
      $result['queryUrl'] = $response->SearchRequestGet->QueryString?(string)$response->SearchRequestGet->QueryString:'';
      $result['ResultId'] = $record->ResultId ? (integer) $record->ResultId : '';
      $result['DbId'] = $record->Header->DbId ? (string) $record->Header->DbId : '';
      $result['DbLabel'] = $record->Header->DbLabel ? (string) $record->Header->DbLabel:'';
      $result['An'] = $record->Header->An ? (string) $record->Header->An : '';
      $result['PLink'] = $record->PLink ? (string) $record->PLink : '';
      $result['PDF'] = $record->FullText->Links ? (string) $record->FullText->Links->Link->Type : '';
      $result['HTML'] = $record->FullText->Text->Availability? (string) $record->FullText->Text->Availability : '';
      if (!empty($record->ImageInfo->CoverArt)) {
        foreach ($record->ImageInfo->CoverArt as $image) {
          $size = (string) $image->Size;
          $target = (string) $image->Target;
          $result['ImageInfo'][$size] = $target;
        }
      } else {
        $result['ImageInfo'] = '';
      }

      $result['FullText'] = $record->FullText ? (string) $record->FullText : '';

      if ($record->CustomLinks) {
        $result['CustomLinks'] = array();
        if ($record->CustomLinks->CustomLink) {
          foreach ($record->CustomLinks->CustomLink as $customLink) {
            $category = $customLink->Category ? (string) $customLink->Category : '';
            $icon = $customLink->Icon ? (string) $customLink->Icon : '';
            $mouseOverText = $customLink->MouseOverText ? (string) $customLink->MouseOverText : '';
            $name = $customLink->Name ? (string) $customLink->Name : '';
            $text = $customLink->Text ? (string) $customLink->Text : '';
            $url = $customLink->Url ? (string) $customLink->Url : '';
            $result['CustomLinks'][] = array(
              'Category'      => $category,
              'Icon'          => $icon,
              'MouseOverText' => $mouseOverText,
              'Name'          => $name,
              'Text'          => $text,
              'Url'           => $url
            );
          }
        }
      }

      if($record->Items) {
        $result['Items'] = array();
        foreach ($record->Items->Item as $item) {
          $label = $item->Label ? (string) $item->Label : '';
          $group = $item->Group ? (string) $item->Group : '';
          $data = $item->Data ? (string) $item->Data : '';
          $result['Items'][$group][] = array(
            'Label' => $label,
            'Group' => $group,
            'Data'  => $this->toHTML($data, $group)
          );
        }
      }

      if($record->RecordInfo) {
        $result['RecordInfo'] = array();
        if ($record->RecordInfo->BibRecord->BibRelationships->IsPartOfRelationships->IsPartOf->BibEntity->Identifiers->Identifier) {
          foreach ($record->RecordInfo->BibRecord->BibRelationships->IsPartOfRelationships->IsPartOf->BibEntity->Identifiers->Identifier as $identifier) {
            $type = $identifier->Type ? (string) $identifier->Type : '';
            $value = $identifier->Value ? (string) $identifier->Value : '';
            $result['RecordInfo'][] = array(
              'Type' => $type,

              'Value' => $value
            );
          }
        }
      }

      if($record->RecordInfo) {
        $result['Identifier'] = array();
        if ($record->RecordInfo->BibRecord->BibEntity->Identifiers->Identifier) {
          foreach ($record->RecordInfo->BibRecord->BibEntity->Identifiers->Identifier as $identifier) {
            $type = $identifier->Type ? (string) $identifier->Type : '';
            $value = $identifier->Value ? (string) $identifier->Value : '';
            $result['Identifier'][] = array(
              'Type' => $type,
              'Value' => $value
            );
          }
        }
      }


      $results[] = $result;
    }
    return $results;
  }

  // This function uses the Search XML response to create an array of the records in the results page
  private function buildStarter($response) {
    $results = array();

    $records = $response->SearchResult->RelatedContent->RelatedRecords->RelatedRecord->Records->Record;

    foreach ($records as $record) {
      $result = array();
      $result['pubType'] = $record -> Header-> PubType?(string)$record ->Header-> PubType:'';
      $result['PubTypeId']= $record->Header->PubTypeId? (string) $record->Header->PubTypeId:'';
      $result['queryUrl'] = $response->SearchRequestGet->QueryString?(string)$response->SearchRequestGet->QueryString:'';
      $result['ResultId'] = $record->ResultId ? (integer) $record->ResultId : '';
      $result['DbId'] = $record->Header->DbId ? (string) $record->Header->DbId : '';
      $result['DbLabel'] = $record->Header->DbLabel ? (string) $record->Header->DbLabel:'';
      $result['An'] = $record->Header->An ? (string) $record->Header->An : '';
      $result['PLink'] = $record->PLink ? (string) $record->PLink : '';
      $result['PDF'] = $record->FullText->Links ? (string) $record->FullText->Links->Link->Type : '';
      $result['HTML'] = $record->FullText->Text->Availability? (string) $record->FullText->Text->Availability : '';
      if (!empty($record->ImageInfo->CoverArt)) {
        foreach ($record->ImageInfo->CoverArt as $image) {
          $size = (string) $image->Size;
          $target = (string) $image->Target;
          $result['ImageInfo'][$size] = $target;
        }
      } else {
        $result['ImageInfo'] = '';
      }

      $result['FullText'] = $record->FullText ? (string) $record->FullText : '';

      if ($record->CustomLinks) {
        $result['CustomLinks'] = array();
        if ($record->CustomLinks->CustomLink) {
          foreach ($record->CustomLinks->CustomLink as $customLink) {
            $category = $customLink->Category ? (string) $customLink->Category : '';
            $icon = $customLink->Icon ? (string) $customLink->Icon : '';
            $mouseOverText = $customLink->MouseOverText ? (string) $customLink->MouseOverText : '';
            $name = $customLink->Name ? (string) $customLink->Name : '';
            $text = $customLink->Text ? (string) $customLink->Text : '';
            $url = $customLink->Url ? (string) $customLink->Url : '';
            $result['CustomLinks'][] = array(
              'Category'      => $category,
              'Icon'          => $icon,
              'MouseOverText' => $mouseOverText,
              'Name'          => $name,
              'Text'          => $text,
              'Url'           => $url
            );
          }
        }
      }

      if($record->Items) {
        $result['Items'] = array();
        foreach ($record->Items->Item as $item) {
          $label = $item->Label ? (string) $item->Label : '';
          $group = $item->Group ? (string) $item->Group : '';
          $data = $item->Data ? (string) $item->Data : '';
          $result['Items'][$group][] = array(
            'Label' => $label,
            'Group' => $group,
            'Data'  => $this->toHTML($data, $group)
          );
        }
      }

      if($record->RecordInfo) {
        $result['RecordInfo'] = array();
        if ($record->RecordInfo->BibRecord->BibRelationships->IsPartOfRelationships->IsPartOf->BibEntity->Identifiers->Identifier) {
          foreach ($record->RecordInfo->BibRecord->BibRelationships->IsPartOfRelationships->IsPartOf->BibEntity->Identifiers->Identifier as $identifier) {
            $type = $identifier->Type ? (string) $identifier->Type : '';
            $value = $identifier->Value ? (string) $identifier->Value : '';
            $result['RecordInfo'][] = array(
              'Type' => $type,

              'Value' => $value
            );
          }
        }
      }

      if($record->RecordInfo) {
        $result['Identifier'] = array();
        if ($record->RecordInfo->BibRecord->BibEntity->Identifiers->Identifier) {
          foreach ($record->RecordInfo->BibRecord->BibEntity->Identifiers->Identifier as $identifier) {
            $type = $identifier->Type ? (string) $identifier->Type : '';
            $value = $identifier->Value ? (string) $identifier->Value : '';
            $result['Identifier'][] = array(
              'Type' => $type,
              'Value' => $value
            );
          }
        }
      }


      $results[] = $result;
    }
    return $results;
  }

  // This function maps the radio buttons below the search box to the field codes expected by the API
  public function fieldCodeSelect($term) {
    if($term=='Author'){
      return 'AU';
    }
    if($term == 'title'){
      return 'TI';
    }
    if($term == 'keyword'){
      return '';
    }
    else{
      return $term;
    }
  }

  // This function replaces the non standard HTML tags in the API response with standard HTML
  private function toHTML($data, $group = '') {
    global $path;
    $path = 'eds';
    // Any group can be added here, but we only use Au (Author)
    // Other groups, not present here, won't be transformed to HTML links
    $allowed_searchlink_groups = array('Au','Su');
    $allowed_link_groups = array('URL');
    // Map xml tags to the HTML tags
    // This is just a small list, the total number of xml tags is far more greater
    $xml_to_html_tags = array(
      '<jsection'    => '<section',
      '</jsection'   => '</section',
      '<highlight'   => '<span class="highlight"',
      '<highligh'    => '<span class="highlight"', // Temporary bug fix
      '</highlight>' => '</span>', // Temporary bug fix
      '</highligh'   => '</span>',
      '<text'        => '<div',
      '</text'       => '</div',
      '<title'       => '<h2',
      '</title'      => '</h2',
      '<anid'        => '<p',
      '</anid'       => '</p',
      '<aug'         => '<strong',
      '</aug'        => '</strong',
      '<hd'          => '<h3',
      '</hd'         => '</h3',
      '<linebr'      => '<br',
      '</linebr'     => '',
      '<olist'       => '<ol',
      '</olist'      => '</ol',
      '<reflink'     => '<a',
      '</reflink'    => '</a',
      '<blist'       => '<p class="blist"',
      '</blist'      => '</p',
      '<bibl'        => '<a',
      '</bibl'       => '</a',
      '<bibtext'     => '<span',
      '</bibtext'    => '</span',
      '<ref'         => '<div class="ref"',
      '</ref'        => '</div',
      '<ulink'       => '<a',
      '</ulink'      => '</a',
      '<superscript' => '<sup',
      '</superscript'=> '</sup',
      '<relatesTo'   => '<sup',
      '</relatesTo'  => '</sup',
      '<script'      => '',
      '</script'     => ''
    );

    // Map xml types to Search types used by the UI
    $xml_to_search_types = array(
      'Au' => 'Author',
      'Su' => 'Subject'
    );

    //  The XML data is XML escaped, let's unescape html entities (e.g. &lt; => <)
    $data = html_entity_decode($data);

    // Start parsing the xml data
    if (!empty($data)) {
      // Replace the XML tags with HTML tags
      $search = array_keys($xml_to_html_tags);
      $replace = array_values($xml_to_html_tags);
      $data = str_replace($search, $replace, $data);

      if (!empty($_REQUEST['ff'])) {
        $facet_terms = $_REQUEST['ff'];
        $facet_string = "";
        if (!empty($facet_terms)) {
          foreach ($facet_terms as $facet) {
            $facet_string .= "&ff[]=" . $facet;
          }
        }
      } else {
        $facet_string = "";
      }

      // Temporary : fix unclosed tags
      $data = preg_replace('/<\/highlight/', '</span>', $data);
      $data = preg_replace('/<\/span>>/', '</span>', $data);
      $data = preg_replace('/<\/searchLink/', '</searchLink>', $data);
      $data = preg_replace('/<\/searchLink>>/', '</searchLink>', $data);

      // Parse searchLinks
      if (!empty($group) && in_array($group, $allowed_searchlink_groups)) {
        $type = $xml_to_search_types[$group];
        $link_xml = '/<searchLink fieldCode="([^"]*)" term="([^"]*)">/';
        $link_html = "<a href=\"".base_path()."$path?search=y&query=$2&type=$1$facet_string\">";
        $data = preg_replace($link_xml, $link_html, $data);
        $data = str_replace('</searchLink>', '</a>', $data);
        $data = str_replace('<br />','; ',$data);
      }
      // Parse link
      if (!empty($group) && in_array($group, $allowed_link_groups)) {
        $link_xml = '/<link linkTarget="([^"]*)" linkTerm="([^"]*)" linkWindow="([^"]*)">/';
        $link_html = "<a name=\"$1\" href=\"$2\" target=\"$3\">";
        $data = preg_replace($link_xml, $link_html, $data);
        $data = str_replace('</link>', '</a>', $data);
      }
      // Replace the rest of searchLinks with simple spans
      $link_xml = '/<searchLink fieldCode="([^\"]*)" term="%22([^\"]*)%22">/';
      $link_html = '<span>';
      $data = preg_replace($link_xml, $link_html, $data);
      $data = str_replace('</searchLink>', '</span>', $data);
    }
    return $data;
  }

  /**
   * This function is for making a retrieve call to the search API.
   * A retrieve call simply give the information for a single record
   * according to the VSIP Record format. Check documentation for more
   * details
   *
   * @param string accession_number
   *  The accession number for the item that is to be queried
   * @param string database
   *  The database ID for the item.
   *
   * @return object
   *  returns a VSIP record object for the single item
   */
  function retrieve($accession_number, $database){
    $url = '';
    if(empty($this->sid)){
      $url = "http://eds-api.ebscohost.com/edsapi/rest/retrieve/$database/$accession_number";
    } else {
      $url = "http://eds-api.ebscohost.com/edsapi/rest/retrieve/$database/$accession_number?sid=$this->sid";
    }
    return $this->execute_single($accession_number, $database);
  }

  public function errorHandling($ch, $response) {
    // Parse the response
    // In case of errors, throw 2 type of exceptions
    // EDSException if the API returned an error message
    // Exception in all other cases. Should be improved for better handling
    if ($response === false) {
      throw new Exception(curl_error($ch));
      curl_close($ch);
    } else {
      $code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
      curl_close($ch);

      switch ($code) {
        case self::HTTP_OK:
          $xml = simplexml_load_string($response);
          if ($xml === false) {
            throw new Exception('Error while parsing the response.');
          } else {
            $xml = simplexml_load_string($response);
            return $xml;
          }
          break;
        case self::HTTP_BAD_REQUEST:
          // re-load EDS token if expired
          $connector = new EDSConnector();
          $connector->authorizer();

          variable_set('hf_stacks_search_eds_authenticationToken', $connector->getAuthToken());
          variable_set('hf_stacks_search_eds_authenticationToken_expiry', date("d-m-Y h:i:s",time() + (15)));
          variable_set('hf_stacks_search_eds_sessionToken', $connector ->getSessionToken($connector->getAuthToken()));
          variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));
          
          // parse results from XML
          $xml = simplexml_load_string($response);
          if ($xml === false) {
            throw new Exception('Error while parsing the response.');
          } else {
            // If the response is an API error
            $error = ''; $code = 0;
            $isError = isset($xml->ErrorNumber) || isset($xml->ErrorCode);
            if ($isError) {
              if (isset($xml->DetailedErrorDescription) && !empty($xml->DetailedErrorDescription)) {
                $error = (string) $xml->DetailedErrorDescription;
              } else if (isset($xml->ErrorDescription)) {
                $error = (string) $xml->ErrorDescription;
              } else if (isset($xml->Reason)) {
                $error = (string) $xml->Reason;
              }
              if (isset($xml->ErrorNumber)) {
                $code = (integer) $xml->ErrorNumber;
              } else if (isset($xml->ErrorCode)) {
                $code = (integer) $xml->ErrorCode;
              }
              //throw new EDSException($error, $code);
            } else {
              throw new Exception('The request could not be understood by the server
                            due to malformed syntax. Modify your search before retrying.');
            }
          }
          break;
        case self::HTTP_NOT_FOUND:
          throw new Exception('The resource you are looking for might have been removed,
                        had its name changed, or is temporarily unavailable.');
          break;
        case self::HTTP_INTERNAL_SERVER_ERROR:
          throw new Exception('The server encountered an unexpected condition which prevented
                        it from fulfilling the request.');
          break;
        // Other HTTP status codes
        default:
          throw new Exception('Unexpected HTTP error.');
          break;
      }
    }
  }

  // This function uses the Search XML response to create an array that stores the search results data
  private function buildFacets($response) {
    $hits = (integer) $response->SearchResult->Statistics->TotalHits;

    $records = array();
    if ($hits > 0) {
      $records = $this->buildFacet($response);
    }

    $results = array(
      'recordCount' => $hits,
      'records'     => $records
    );

    return $records;
  }

  private function buildFacet($response) {
    $results = array();

    $facets = $response->SearchResult->AvailableFacets->AvailableFacet;

    foreach ($facets as $facet) {
      $values = array();
      foreach ($facet->AvailableFacetValues->AvailableFacetValue as $value) {
        $this_value = (string) $value->Value;
        $this_value = str_replace(array('\(','\)'), array('(', ')'), $this_value);
        $this_action = (string) $value->AddAction;
        $this_action = str_replace(array('\(','\)'), array('(', ')'), $this_action);
        $values[] = array(
          'Value'  => $this_value,
          'Action' => $this_action,
          'Count'  => (string) $value->Count
        );
      }
      $id = (string) $facet->Id;
      $label = (string) $facet->Label;
      if (!empty($label)) {
        $results[] = array(
          'Id'        => $id,
          'Label'     => $label,
          'Values'    => $values,
          'isApplied' => false
        );
      }
    }

    return $results;
  }

}
