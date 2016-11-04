<?php
/**
 * EDSException class
 * Used when EBSCO API calls return error messages
 */
class EDSException extends Exception {
  const CRITICAL_ERROR = 1;

  // Make message argument mandatory
  public function __construct($message, $code = self::CRITICAL_ERROR, Exception $previous = null) {
    parent::__construct($message, $code, $previous);
  }
}

/**
 * Connector Class for Authentication Against EBSCO EDS Server
 */

class EDSConnector {
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

  /**
   * Constructor to set up the EDSConnector class
   */
  function __construct() {

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

  public function authorizer() {
    $END_POINT = variable_get('stacks_eds_server');
    $USER_ID = variable_get('stacks_eds_user','');
    $PASSWORD = variable_get('stacks_eds_pass','');
    $PROFILE = variable_get('stacks_eds_profile','');
    $ORG_ID = variable_get('stacks_eds_org','');

    $authenticationTokenExpiry = variable_get('hf_stacks_search_eds_authenticationToken_expiry');
    $sessionTokenExpiry = variable_get('hf_stacks_search_eds_sessionToken_expiry');

    $currentTime = date("d-m-Y h:i:s", time());

    //if ((!empty($END_POINT)) && (!empty($USER_ID)) && (!empty($PASSWORD)) && (!empty($PROFILE)) && (!empty($ORG_ID))) {
    if ((!empty($END_POINT)) && (!empty($USER_ID)) && (!empty($PASSWORD)) && (!empty($PROFILE))) {

      if ($currentTime >= $authenticationTokenExpiry || $currentTime >= $sessionTokenExpiry ) {
        $authToken = $this->getAuthToken();
        $sessionToken = $this->getSessionToken($authToken);

        variable_set('hf_stacks_search_eds_authenticationToken', $authToken);
        variable_set('hf_stacks_search_eds_sessionToken', $sessionToken);
        //Set time interval to preconfigured time
        variable_set('hf_stacks_search_eds_authenticationToken_expiry', date("d-m-Y h:i:s",time() + (15)));
        variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));
      } else {
        $authToken = variable_get('hf_stacks_search_eds_authenticationToken');
        $sessionToken = variable_get('hf_stacks_search_eds_sessionToken');
      }

    } else {
      return 'error';
    }
  }


  public function getAuthToken() {
    $result = $this->requestAuthenticationToken();
    return $result['authenticationToken'];
  }

  /**
   * Request the authentication token
   */
  // This function calls the UID Authenticate method using HTTP POST and fetches the auth token
  public function requestAuthenticationToken() {
    $END_POINT = variable_get('stacks_eds_server');
    $USER_ID = variable_get('stacks_eds_user','');
    $PASSWORD = variable_get('stacks_eds_pass','');
    $PROFILE = variable_get('stacks_eds_profile','');
    $ORG_ID = variable_get('stacks_eds_org','');

    $authenticationTokenExpiry = variable_get('hf_stacks_search_eds_authenticationToken_expiry');

    $currentTime = date("d-m-Y h:i:s", time());

    $url = self::$AUTH_END_POINT . '/UIDAuth';
    $userID = $USER_ID;
    $password = $PASSWORD;
    $interfaceID = $ORG_ID;

    // Add the body of the request. Important. UserId and Password are to the API profile
    // UserID: customer’s EDS API user ID
    // Password: customer’s EDS API password
    // InterfaceID: optional string, use "api"
    /*
    $params =<<<BODY
<UIDAuthRequestMessage xmlns="http://www.ebscohost.com/services/public/AuthService/Response/2012/06/01">
    <UserId>$userID</UserId>
    <Password>$password</Password>
    <InterfaceId>$interfaceID</InterfaceId>
</UIDAuthRequestMessage>
BODY;

    // Set the content type to 'application/xml'.
    $headers = array(
      'Content-Type: application/xml',
      'Content-Length: ' . strlen($params),
      'Accept-Encoding: gzip,deflate'
    );
    */

    $data = array("UserId" => $userID, "Password" => $password, "InterfaceId" => $interfaceID);
    $params = json_encode($data);

    // Set the content type to 'application/json'.
    $headers = array(
      'Content-Type: application/json',
      'Content-Length: ' . strlen($params),
      'Accept-Encoding: gzip,deflate'
    );

    $response = $this->sendHTTPRequest($url, $params, $headers, 'POST');
    $response = $this->buildAuthenticationToken($response);

    return $response;
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
      // GET method
      if ($method == 'GET') {
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'GET');

        $query = http_build_query($params);
        // replace query params like facet[0]=value with facet=value
        $query = preg_replace('/%5B(?:[0-9]|[1-9][0-9]+)%5D=/', '=', $query);
        $url .= '?' . $query;
        curl_setopt($ch, CURLOPT_URL, $url);
        // POST method
      } else {
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

  // This function receives the XML response to the Authenticate method call, and creates a auth token
  private function buildAuthenticationToken($response) {
    $token = (string) $response->AuthToken;
    $timeout = (integer) $response->AuthTimeout;

    $result = array(
      'authenticationToken'   => $token,
      'authenticationTimeout' => $timeout,
      'authenticationTimeStamp'=> time()
    );
    return $result;
  }

  /**
   * Get session token for a profile
   * If session token is not available
   * a new session token will be generated
   */
  public function getSessionToken($authenToken, $invalid='n') {
    /*
    $sessionTokenExpiry = variable_get('hf_stacks_search_eds_sessionToken_expiry');
    $currentTime = date("d-m-Y h:i:s", time());
    if($currentTime >= $sessionTokenExpiry ) {
    */
      $token = '';

      $sessionToken = $this->requestSessionToken($authenToken);
      $sessionTokenExpiry = variable_get('hf_stacks_search_eds_sessionToken_expiry');

      variable_set('hf_stacks_search_eds_sessionToken', $sessionToken);
      variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));
    /*
    } else {
      $sessionToken = variable_get('hf_stacks_search_eds_sessionToken');
    }
    */

    $token = $sessionToken;

    return $token;
  }

  // calls the CreateSession method using HTTP GET and fetches the session token
  public function requestSessionToken($authenToken) {
    $END_POINT = variable_get('stacks_eds_server');
    $USER_ID = variable_get('stacks_eds_user','');
    $PASSWORD = variable_get('stacks_eds_pass','');
    $PROFILE = variable_get('stacks_eds_profile','');
    $ORG_ID = variable_get('stacks_eds_org','');

    $authenticationTokenExpiry = variable_get('hf_stacks_search_eds_authenticationToken_expiry');
    $sessionTokenExpiry = variable_get('hf_stacks_search_eds_sessionToken_expiry');

    $currentTime = date("d-m-Y h:i:s", time());

    $url = $END_POINT . '/CreateSession';
    $profile = $PROFILE;
    $orgID = $ORG_ID;
    $guest = 'y';

    // add the HTTP query parameters
    // if you are a vendor working on behalf of a customer then “org” must be filled in per your agreement
    // please note proper use of the “guest” setting per Terms Of Use i.e. must be set to ‘y’ if you are not making sufficient effort to authenticate users to your institution
    $params = array(
      'profile' => $profile,
      'org'     => $orgID,
      'guest'   => $guest
    );

    $headers = array(
      'x-authenticationToken: ' . $authenToken
    );

    $response = $this->sendHTTPRequest($url, $params, $headers);
    $response = $this->buildSessionToken($response);
    return $response;
  }

  // This function receives the XML response to the CreateSession method call, and creates a session token
  private function buildSessionToken($response) {
    $token = (string) $response->SessionToken;
    return $token;
  }

  // This function calls the Search method with the user’s query
  public function requestSearch() {
    $END_POINT = variable_get('stacks_eds_server');
    $USER_ID = variable_get('stacks_eds_user','');
    $PASSWORD = variable_get('stacks_eds_pass','');
    $PROFILE = variable_get('stacks_eds_profile','');
    $ORG_ID = variable_get('stacks_eds_org','');

    try {
      $url = $END_POINT . '/Search';

      if (isset($_REQUEST['ff'])) {
        $ff = $_REQUEST['ff'];
      } else {
        $ff = "";
      }

      // Build  the arguments for the Search API method
      $query = str_replace('"','',$_REQUEST['query']);
      $search = array(
        'query' => $query,
        'ff'    => $ff
      );

      /*
       * Set search parameters for the Search API method
       */
      //$start = 2;
      $start = isset($_REQUEST['pagenumber'])?$_REQUEST['pagenumber']:1;
      $start = intval($start);
      $limit = isset($_REQUEST['limit'])?$_REQUEST['limit']:10;
      $sortBy = isset($_REQUEST['sortBy'])?$_REQUEST['sortBy']:'relevance';
      $amount = isset($_REQUEST['amount'])?$_REQUEST['amount']:'detailed';
      $mode = 'all';

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
        $query["query"] = $query_str;
      } else {
        $results = array();
        return $results;
      }
      $query['action'] = array();
      //array_push($query['action'], "GoToPage($start)");
      // Add the HTTP query params
      $params = array(
        'sort'           => $sortBy,
        'searchmode'     => $mode,
        'view'           => $amount,
        'includefacets'  => 'y',
        'resultsperpage' => $limit,
        'pagenumber'     => $start,
        'highlight'      => 'y',
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

      $params = array_merge($params, $query, $facets);

      $authenticationToken = $this->getAuthToken();
      $sessionToken = $this ->getSessionToken($this->getAuthToken());

      // if authentication token is missing then the session token is missing too, so get both tokens
      if (empty($authenticationToken) || empty($sessionToken)) {
        $result = $this->apiAuthenticationAndSessionToken();
        if ($this->isError($result)) {
          // Any error should terminate the request immediately
          // in order to prevent infinite recursion
          return $result;
        }
      }

      $headers = array(
        'x-authenticationToken: ' . $authenticationToken,
        'x-sessionToken: ' . $sessionToken
      );

      $response = '';
      try{
        $response = $this->sendHTTPRequest($url, $params, $headers);
      } catch(EDSException $e) {
        try {
          // Retry the request if there were authentication errors
          $code = $e->getCode();
          switch ($code) {
            case Functions::EDS_AUTH_TOKEN_INVALID:
              if(!empty($authenticationTokenExpiry) || !empty($sessionTokenExpiry)) {
                variable_set('hf_stacks_search_eds_authenticationToken', $this->getAuthToken());
                variable_set('hf_stacks_search_eds_authenticationToken_expiry', date("d-m-Y h:i:s",time() + (15)));
                variable_set('hf_stacks_search_eds_sessionToken', $sessionToken);
                variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));
              }

              return $this->requestSearch();

              break;
            case Functions::EDS_SESSION_TOKEN_INVALID:
              variable_set('hf_stacks_search_eds_authenticationToken', $this->getAuthToken());
              variable_set('hf_stacks_search_eds_authenticationToken_expiry', date("d-m-Y h:i:s",time() + (15)));
              variable_set('hf_stacks_search_eds_sessionToken', $sessionToken);
              variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));

              return $this->requestSearch();

              break;
            default:
              $result = array(
                'error' => $e->getMessage()
              );
              return $result;
              break;
          }
        }  catch(Exception $e) {
          $result = array(
            'error' => $e->getMessage()
          );
          return $result;
        }
      }

      $response = $this->buildSearch($response);

      return $response;

    } catch(Exception $e) {
      $result = array(
        'error' => $e->getMessage()
      );
      return $result;
    }
  }

  // This function calls the Retrieve method with the AN and Database ID of the record that the user clicked on
  public function requestLookup() {
    $END_POINT = variable_get('stacks_eds_server');
    $USER_ID = variable_get('stacks_eds_user','');
    $PASSWORD = variable_get('stacks_eds_pass','');
    $PROFILE = variable_get('stacks_eds_profile','');
    $ORG_ID = variable_get('stacks_eds_org','');

    try {
      $url = $END_POINT . '/Search';

      if (isset($_REQUEST['ff'])) {
        $ff = $_REQUEST['ff'];
      } else {
        $ff = "";
      }

      // Build  the arguments for the Search API method
      $query = str_replace('"','',$_REQUEST['isbn']);
      $search = array(
        'query' => $query,
        'ff'    => $ff
      );

      /*
       * Set search parameters for the Search API method
       */
      //$start = 2;
      $start = isset($_REQUEST['pagenumber'])?$_REQUEST['pagenumber']:1;
      $start = intval($start);
      $limit = isset($_REQUEST['limit'])?$_REQUEST['limit']:10;
      $sortBy = isset($_REQUEST['sortBy'])?$_REQUEST['sortBy']:'relevance';
      $amount = isset($_REQUEST['amount'])?$_REQUEST['amount']:'detailed';
      $mode = 'all';

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
        $query["query"] = $query_str;
      } else {
        $results = array();
        return $results;
      }
      $query['action'] = array();
      //array_push($query['action'], "GoToPage($start)");
      // Add the HTTP query params
      $params = array(
        'sort'           => $sortBy,
        'searchmode'     => $mode,
        'view'           => $amount,
        'includefacets'  => 'y',
        'resultsperpage' => $limit,
        'pagenumber'     => $start,
        'highlight'      => 'y',
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

      $params = array_merge($params, $query, $facets);

      $authenticationToken = $this->getAuthToken();
      $sessionToken = $this ->getSessionToken($this->getAuthToken());

      $headers = array(
        'x-authenticationToken: ' . $authenticationToken,
        'x-sessionToken: ' . $sessionToken
      );

      $response = '';
      try{
        $response = $this->sendHTTPRequest($url, $params, $headers);
      } catch(EDSException $e) {
        try {
          // Retry the request if there were authentication errors
          $code = $e->getCode();
          switch ($code) {
            case Functions::EDS_AUTH_TOKEN_INVALID:
              if(!empty($authenticationTokenExpiry) || !empty($sessionTokenExpiry)) {
                variable_set('hf_stacks_search_eds_authenticationToken', $this->getAuthToken());
                variable_set('hf_stacks_search_eds_authenticationToken_expiry', date("d-m-Y h:i:s",time() + (15)));
                variable_set('hf_stacks_search_eds_sessionToken', $sessionToken);
                variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));
              }

              return $this->requestLookup();

              break;
            case Functions::EDS_SESSION_TOKEN_INVALID:
              variable_set('hf_stacks_search_eds_sessionToken', $this->getSessionToken($authenticationToken,'y'));
              variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));

              return $this->requestSearch();

              break;
            default:
              $result = array(
                'error' => $e->getMessage()
              );
              return $result;
              break;
          }
        }  catch(Exception $e) {
          $result = array(
            'error' => $e->getMessage()
          );
          return $result;
        }
      }

      $response = $this->buildSearch($response);

      return $response;

    } catch(Exception $e) {
      $result = array(
        'error' => $e->getMessage()
      );
      return $result;
    }
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
          $result['Items'][$group][] = array(
            'Label' => $label,
            'Group' => $group,
            'Data'  => $this->toHTML($data, $group)
          );
        }
      }
      $results[] = $result;
    }
    return $results;
  }

  // This function calls the Retrieve method with the AN and Database ID of the record that the user clicked on
  public function requestRetrieve() {
    $END_POINT = variable_get('stacks_eds_server');
    $USER_ID = variable_get('stacks_eds_user','');
    $PASSWORD = variable_get('stacks_eds_pass','');
    $PROFILE = variable_get('stacks_eds_profile','');
    $ORG_ID = variable_get('stacks_eds_org','');

    try{
      $url = $END_POINT . '/Retrieve';

      $db = $_REQUEST['db'];
      $an = $_REQUEST['an'];
      if (!empty($_REQUEST['query'])) {
        $highlight = $_REQUEST['query'];
        $highlight = str_replace(array(" ","&","-"),array(","),$highlight);
      } else {
        $highlight = '';
      }

      $authenticationToken = $this->getAuthToken();
      $sessionToken = $this->getSessionToken($this->getAuthToken());

      $params = array(
        'an'        => $an,
        'dbid'      => $db,
        'highlightterms' => $highlight
      );

      $headers = array(
        'x-authenticationToken: ' . $authenticationToken,
        'x-sessionToken: ' . $sessionToken
      );

      $response="";
      try{
        $response = $this->sendHTTPRequest($url, $params, $headers);
      }catch(EDSException $e) {
        try {
          // Retry the request if there were authentication errors
          $code = $e->getCode();
          switch ($code) {
            case Functions::EDS_AUTH_TOKEN_INVALID:
              if(!empty($authenticationTokenExpiry) || !empty($sessionTokenExpiry)) {
                variable_set('hf_stacks_search_eds_authenticationToken', $this->getAuthToken());
                variable_set('hf_stacks_search_eds_authenticationToken_expiry', date("d-m-Y h:i:s",time() + (15)));
                variable_set('hf_stacks_search_eds_sessionToken', $sessionToken);
                variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));
              }

              return $this->requestRetrieve();

              break;
            case Functions::EDS_SESSION_TOKEN_INVALID:
              if(!empty($authenticationTokenExpiry) || !empty($sessionTokenExpiry)) {
                variable_set('hf_stacks_search_eds_sessionToken', $this->getSessionToken($authenticationToken,'y'));
                variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));
              }

              return $this->requestRetrieve();

              break;
            default:
              $result = array(
                'error' => $e->getMessage()
              );
              return $result;
              break;
          }
        }  catch(Exception $e) {
          $result = array(
            'error' => $e->getMessage()
          );
          return $result;
        }
      }
      $response = $this->buildRetrieve($response);
      return $response;
    } catch(Exception $e) {
      $result = array(
        'error' => $e->getMessage()
      );
      return $result;
    }
  }

  // This function calls the Retrieve method with the AN and Database ID of the record that the user clicked on
  public function requestSavelist($an, $db) {
    $END_POINT = variable_get('stacks_eds_server');
    $USER_ID = variable_get('stacks_eds_user','');
    $PASSWORD = variable_get('stacks_eds_pass','');
    $PROFILE = variable_get('stacks_eds_profile','');
    $ORG_ID = variable_get('stacks_eds_org','');

    try{
      $url = $END_POINT . '/Retrieve';

      $authenticationToken = $this->getAuthToken();
      $sessionToken = $this->getSessionToken($authenticationToken);

      $params = array(
        'an'        => $an,
        'dbid'      => $db
      );

      $headers = array(
        'x-authenticationToken: ' . $authenticationToken,
        'x-sessionToken: ' . $sessionToken
      );

      $response="";
      try{
        $response = $this->sendHTTPRequest($url, $params, $headers);
      }catch(EDSException $e) {
        try {
          // Retry the request if there were authentication errors
          $code = $e->getCode();
          switch ($code) {
            case Functions::EDS_AUTH_TOKEN_INVALID:
              $authenticationTokenExpiry = variable_get('hf_stacks_search_eds_authenticationToken_expiry');
              $sessionTokenExpiry = variable_get('hf_stacks_search_eds_sessionToken_expiry');

              if(!empty($authenticationTokenExpiry) || !empty($sessionTokenExpiry)) {
                variable_set('hf_stacks_search_eds_authenticationToken', $this->getAuthToken());
                variable_set('hf_stacks_search_eds_authenticationToken_expiry', date("d-m-Y h:i:s",time() + (15)));
                variable_set('hf_stacks_search_eds_sessionToken', $sessionToken);
                variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));
              }

              return $this->requestRetrieve();

              break;
            case Functions::EDS_SESSION_TOKEN_INVALID:
              variable_set('hf_stacks_search_eds_sessionToken', $this->getSessionToken($authenticationToken,'y'));
              variable_set('hf_stacks_search_eds_sessionToken_expiry', date("d-m-Y h:i:s",time() + (15)));

              return $this->requestRetrieve();

              break;
            default:
              $result = array(
                'error' => $e->getMessage()
              );
              return $result;
              break;
          }
        }  catch(Exception $e) {
          $result = array(
            'error' => $e->getMessage()
          );
          return $result;
        }
      }
      $response = $this->buildRetrieve($response);
      return $response;
    } catch(Exception $e) {
      $result = array(
        'error' => $e->getMessage()
      );
      return $result;
    }
  }

  // This function uses the Retrieve XML response to create an array of the record in the detailed record page
  private function buildRetrieve($response) {
    $record = $response->Record;

    if ($record) {
      $record = $record[0]; // there is only one record
    }

    $readonline = '';

    //$link_1 = $record->PLink ? (string) $record->PLink : '';
    $link_2 = $record->CustomLinks ? (string) $record->CustomLinks : '';
    $link_3 = $record->FullText->CustomLinks ? (string) $record->FullText->CustomLinks : '';
    $link_4 = $record->Items->Item['Group=URL']->Data ? (string) $record->Items->Item['Group=URL']->Data : '';
    $link_5 = $record->FullText->Links['Type=other'] ? (string) $record->FullText->Links['Type=other'] : '';
    $link_6 = $record->FullText->Links['Type=pdflink'] ? (string) $record->FullText->Links['Type=pdflink'] : '';

    //if (!empty($link_1)) {$readonline = $link_1; }
    if (!empty($link_2)) {$readonline = $link_2; }
    if (!empty($link_3)) {$readonline = $link_3; }
    if (!empty($link_4)) {$readonline = $link_4; }
    if (!empty($link_5)) {$readonline = $link_5; }
    if (!empty($link_6)) {$readonline = $link_6; }

    $result = array();
    $result['AccessLevel'] = $record->Header->AccessLevel?(string)$record->Header -> AccessLevel:'';
    $result['pubType'] = $record -> Header->PubType? (string)$record -> Header-> PubType:'';
    $result['PubTypeId']= $record->Header->PubTypeId? (string) $record->Header->PubTypeId:'';
    $result['DbId'] = $record->Header->DbId ? (string) $record->Header->DbId : '';
    $result['DbLabel'] = $record->Header->DbLabel ? (string) $record->Header->DbLabel:'';
    $result['An'] = $record->Header->An ? (string) $record->Header->An : '';
    $result['PLink'] = $record->PLink ? (string) $record->PLink : '';
    $result['pdflink'] = $record->FullText->Links ? (string) $record->FullText->Links->Link->Url : '';
    $result['ReadOnline'] = $readonline;
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

  // This function replaces the non standard HTML tags in the API response with standard HTML
  private function toHTML($data, $group = '') {
    global $path;
    $path = '/eds';
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

      // Temporary : fix unclosed tags
      $data = preg_replace('/<\/highlight/', '</span>', $data);
      $data = preg_replace('/<\/span>>/', '</span>', $data);
      $data = preg_replace('/<\/searchLink/', '</searchLink>', $data);
      $data = preg_replace('/<\/searchLink>>/', '</searchLink>', $data);

      // Parse searchLinks
      if (!empty($group) && in_array($group, $allowed_searchlink_groups)) {
        $type = $xml_to_search_types[$group];
        $link_xml = '/<searchLink fieldCode="([^"]*)" term="([^"]*)">/';
        $link_html = "<a href=\"$path?search=y&query=$2&type=$1\">";
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
      // Parse bibliography (anchors and links)
      //$data = preg_replace('/<a idref="([^\"]*)"/', '<a href="edsapi-simple-app.php$1"', $data);
      //$data = preg_replace('/<a id="([^\"]*)" idref="([^\"]*)" type="([^\"]*)"/', '<a id="$1" href="edsapi-simple-app.php$2"', $data);
    }
    return $data;
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
}
