// Javascript file for primary search form

(function ($) {
  Drupal.behaviors.hf_stacks_search = {
    attach: function (context, settings) {
      var basePath = Drupal.settings.basePath;

      // Animation of hiding the drop-down
      $('input[name="searchsource"]').change(function(){
        //$('#globalSearch').attr('action',$(this).val());
        if ($(this).attr('id') == 'searchsource_website'){
          $('#globalSearch h4').animate({'paddingLeft':'+=104px'}, 'normal');
          $('#globalSearch .select2-container').fadeOut();
        } else {
          $('#globalSearch h4').animate({'paddingLeft':'0px'}, 'normal');
          $('#globalSearch .select2-container').fadeIn();
        }
      });

      // display hidden object for polaris
      var inp = $("#searchBox").val();
      if(jQuery.trim(inp).length > 0)
      {
        if ( ($("input[name=exturl]").val == 'polaris') || ($("input[name=exturl2]").val == 'polaris') || ($("input[name=exturl2]").val == 'polaris') ) {
          $('object[name="session_polaris"]').css("visibility", "visible");
        }
      }

      // website search redirect
      $("#searchSubmit").click(function(e) {
        if ( $('.selectSearchCat').val() == 'eds' ) {
          // eds search
          $("input[name=exturl]").val('');
          $("input[name=exturl2]").val('');
          $("input[name=exturl3]").val('');
          $("input[name=exttype]").val('');
          $("input[name=exttype2]").val('');
          $("input[name=exttype3]").val('');

          var action = $("input[name=edsurl]").val();
          $("#globalSearch").attr("action", action);
          //$("#searchBox").name = 'query';
          $("#searchBox").attr('name', 'query');
        } else if ( $('.selectSearchCat').val() == 'ext' ) {
          // external search (opac)
          $("input[name=edsurl]").val('');
          var action = $("input[name=exturl]").val();
          $("#globalSearch").attr("action", action);
          var type = $("input[name=exttype]").val();
          switch(type) {
            case 'polaris':
              //$("#searchBox").name = 'term';
              $("#searchBox").attr('name', 'term');
              break;
            case 'sirsi':
              $("#searchBox").attr('name', 'qu');
              break;
            case 'iii':
              $("#searchBox").attr('name', 'target');
              break;
            case 'evergreen':
              $("#searchBox").attr('name', 'query');
              break;
            case 'oclc':
              $("#searchBox").attr('name', 'queryString');
              break;
              case 'koha':
              $("#searchBox").attr('name', 'q');
              break;
            case 'exlibris':
              $("#searchBox").attr('name', 'vl(freeText0)');
              break;
            case 'bibliocommons':
              $("#searchBox").attr('name', 'q');
              break;
            case 'vufind':
              $("#searchBox").attr('name', 'lookfor');
              break;
            case 'edsnative':
              e.preventDefault();
              e.stopPropagation();              
              var eds_url = $("input[name=exturl]").val();

              var eds_authtype = $("input[name=eds_authtype]").val();
              var eds_direct = $("input[name=eds_direct]").val();
              var eds_catalogue_url = $("input[name=eds_catalogue_url]").val();
              var eds_user = $("input[name=eds_user]").val();
              var eds_pass = $("input[name=eds_pass]").val();
              var eds_scope = $("input[name=eds_scope]").val();
              var eds_profile = $("input[name=eds_profile]").val();
              var eds_org = $("input[name=eds_org]").val();
              var eds_custid = $("input[name=eds_custid]").val();
              var eds_groupid = $("input[name=eds_groupid]").val();
              var eds_site = $("input[name=eds_site]").val();

              if (eds_authtype == 'athens') {
                eds_url = eds_url + "?direct="+eds_direct+"&site="+eds_site+"&authtype="+eds_authtype+"&custid="+eds_custid+"&groupid="+eds_groupid+"&profile="+eds_profile;
              }
              if (eds_authtype == 'sso') {
                eds_url = eds_url + "?direct="+eds_direct+"&site="+eds_site+"&authtype="+eds_authtype+"&custid="+eds_custid+"&groupid="+eds_groupid+"&profile="+eds_profile;
              }
              if (eds_authtype == 'ip,guest') {
                eds_url = eds_url + "?direct="+eds_direct+"&site="+eds_site+"&authtype="+eds_authtype+"&custid="+eds_custid+"&groupid="+eds_groupid+"&profile="+eds_profile;
              }
              if (eds_authtype == 'uid') {
                eds_url = eds_url + "?direct="+eds_direct+"&authtype="+eds_authtype+"&user="+eds_user+"&password="+eds_pass+"&group="+eds_org+"&profile="+eds_profile+"&scope="+eds_scope;
              }
              eds_url = eds_url + "&bquery=" + $("#searchBox").val();

              //console.log(eds_url);
              $(location).attr('href',eds_url);
              return false;
              break;
            case 'edsnative2':
              e.preventDefault();
              e.stopPropagation();
              var eds_url2 = $("input[name=exturl2]").val();

              var eds_authtype2 = $("input[name=eds_authtype2]").val();
              var eds_direct2 = $("input[name=eds_direct2]").val();
              var eds_catalogue_url2 = $("input[name=eds_catalogue_url2]").val();
              var eds_user2 = $("input[name=eds_user2]").val();
              var eds_pass2 = $("input[name=eds_pass2]").val();
              var eds_scope2 = $("input[name=eds_scope2]").val();
              var eds_profile2 = $("input[name=eds_profile2]").val();
              var eds_org2 = $("input[name=eds_org2]").val();
              var eds_custid2 = $("input[name=eds_custid2]").val();
              var eds_groupid2 = $("input[name=eds_groupid2]").val();
              var eds_site2 = $("input[name=eds_site2]").val();

              if (eds_authtype2 == 'athens') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&site="+eds_site2+"&authtype="+eds_authtype2+"&custid="+eds_custid2+"&groupid="+eds_groupid2+"&profile="+eds_profile2;
              }
              if (eds_authtype2 == 'sso') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&site="+eds_site2+"&authtype="+eds_authtype2+"&custid="+eds_custid2+"&groupid="+eds_groupid2+"&profile="+eds_profile2;
              }
              if (eds_authtype2 == 'ip,guest') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&site="+eds_site2+"&authtype="+eds_authtype2+"&custid="+eds_custid2+"&groupid="+eds_groupid2+"&profile="+eds_profile2;
              }
              if (eds_authtype2 == 'uid') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&authtype="+eds_authtype2+"&user="+eds_user2+"&password="+eds_pass2+"&group="+eds_org2+"&profile="+eds_profile2+"&scope="+eds_scope2;
              }
              eds_url2 = eds_url2 + "&bquery=" + $("#searchBox").val();

              //console.log(eds_url2);
              $(location).attr('href',eds_url2);
              return false;
              break;
            case 'edsnative3':
              e.preventDefault();
              e.stopPropagation();
              var eds_url3 = $("input[name=exturl3]").val();

              var eds_authtype3 = $("input[name=eds_authtype3]").val();
              var eds_direct3 = $("input[name=eds_direct3]").val();
              var eds_catalogue_url3 = $("input[name=eds_catalogue_url3]").val();
              var eds_user3 = $("input[name=eds_user3]").val();
              var eds_pass3 = $("input[name=eds_pass3]").val();
              var eds_scope3 = $("input[name=eds_scope3]").val();
              var eds_profile3 = $("input[name=eds_profile3]").val();
              var eds_org3 = $("input[name=eds_org3]").val();
              var eds_custid3 = $("input[name=eds_custid3]").val();
              var eds_groupid3 = $("input[name=eds_groupid3]").val();
              var eds_site3 = $("input[name=eds_site3]").val();

              if (eds_authtype3 == 'athens') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&site="+eds_site3+"&authtype="+eds_authtype3+"&custid="+eds_custid3+"&groupid="+eds_groupid3+"&profile="+eds_profile3;
              }
              if (eds_authtype3 == 'sso') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&site="+eds_site3+"&authtype="+eds_authtype3+"&custid="+eds_custid3+"&groupid="+eds_groupid3+"&profile="+eds_profile3;
              }
              if (eds_authtype3 == 'ip,guest') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&site="+eds_site3+"&authtype="+eds_authtype3+"&custid="+eds_custid3+"&groupid="+eds_groupid3+"&profile="+eds_profile3;
              }
              if (eds_authtype3 == 'uid') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&authtype="+eds_authtype3+"&user="+eds_user3+"&password="+eds_pass3+"&group="+eds_org3+"&profile="+eds_profile3+"&scope="+eds_scope3;
              }
              eds_url3 = eds_url3 + "&bquery=" + $("#searchBox").val();

              //console.log(eds_url3);
              $(location).attr('href',eds_url3);
              return false;
              break;
            default:
              $("#searchBox").attr('name', 'query');
          }
        } else if ( $('.selectSearchCat').val() == 'ext2' ) {
          // external search (opac)
          $("input[name=edsurl2]").val('');
          var action = $("input[name=exturl2]").val();
          $("#globalSearch").attr("action", action);
          var type = $("input[name=exttype2]").val();
          switch(type) {
            case 'polaris':
              //$("#searchBox").name = 'term';
              $("#searchBox").attr('name', 'term');
              break;
            case 'sirsi':
              $("#searchBox").attr('name', 'qu');
              break;
            case 'iii':
              $("#searchBox").attr('name', 'target');
              break;
            case 'evergreen':
              $("#searchBox").attr('name', 'query');
              break;
            case 'oclc':
              $("#searchBox").attr('name', 'queryString');
              break;
            case 'koha':
              $("#searchBox").attr('name', 'q');
              break;
            case 'exlibris':
              $("#searchBox").attr('name', 'vl(freeText0)');
              break;
            case 'bibliocommons':
              $("#searchBox").attr('name', 'q');
              break;
            case 'vufind':
              $("#searchBox").attr('name', 'lookfor');
              break;
            case 'edsnative':
              e.preventDefault();
              e.stopPropagation();
              var eds_url = $("input[name=exturl2]").val();

              var eds_authtype = $("input[name=eds_authtype]").val();
              var eds_direct = $("input[name=eds_direct]").val();
              var eds_catalogue_url = $("input[name=eds_catalogue_url]").val();
              var eds_user = $("input[name=eds_user]").val();
              var eds_pass = $("input[name=eds_pass]").val();
              var eds_scope = $("input[name=eds_scope]").val();
              var eds_profile = $("input[name=eds_profile]").val();
              var eds_org = $("input[name=eds_org]").val();
              var eds_custid = $("input[name=eds_custid]").val();
              var eds_groupid = $("input[name=eds_groupid]").val();
              var eds_site = $("input[name=eds_site]").val();

              if (eds_authtype == 'athens') {
                eds_url = eds_url + "?direct="+eds_direct+"&site="+eds_site+"&authtype="+eds_authtype+"&custid="+eds_custid+"&groupid="+eds_groupid+"&profile="+eds_profile;
              }
              if (eds_authtype == 'sso') {
                eds_url = eds_url + "?direct="+eds_direct+"&site="+eds_site+"&authtype="+eds_authtype+"&custid="+eds_custid+"&groupid="+eds_groupid+"&profile="+eds_profile;
              }
              if (eds_authtype == 'ip,guest') {
                eds_url = eds_url + "?direct="+eds_direct+"&site="+eds_site+"&authtype="+eds_authtype+"&custid="+eds_custid+"&groupid="+eds_groupid+"&profile="+eds_profile;
              }
              if (eds_authtype == 'uid') {
                eds_url = eds_url + "?direct="+eds_direct+"&authtype="+eds_authtype+"&user="+eds_user+"&password="+eds_pass+"&group="+eds_org+"&profile="+eds_profile+"&scope="+eds_scope;
              }
              eds_url = eds_url + "&bquery=" + $("#searchBox").val();

              //console.log(eds_url);
              $(location).attr('href',eds_url);
              return false;
              break;
            case 'edsnative2':
              e.preventDefault();
              e.stopPropagation();
              var eds_url2 = $("input[name=exturl2]").val();

              var eds_authtype2 = $("input[name=eds_authtype2]").val();
              var eds_direct2 = $("input[name=eds_direct2]").val();
              var eds_catalogue_url2 = $("input[name=eds_catalogue_url2]").val();
              var eds_user2 = $("input[name=eds_user2]").val();
              var eds_pass2 = $("input[name=eds_pass2]").val();
              var eds_scope2 = $("input[name=eds_scope2]").val();
              var eds_profile2 = $("input[name=eds_profile2]").val();
              var eds_org2 = $("input[name=eds_org2]").val();
              var eds_custid2 = $("input[name=eds_custid2]").val();
              var eds_groupid2 = $("input[name=eds_groupid2]").val();
              var eds_site2 = $("input[name=eds_site2]").val();

              if (eds_authtype2 == 'athens') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&site="+eds_site2+"&authtype="+eds_authtype2+"&custid="+eds_custid2+"&groupid="+eds_groupid2+"&profile="+eds_profile2;
              }
              if (eds_authtype2 == 'sso') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&site="+eds_site2+"&authtype="+eds_authtype2+"&custid="+eds_custid2+"&groupid="+eds_groupid2+"&profile="+eds_profile2;
              }
              if (eds_authtype2 == 'ip,guest') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&site="+eds_site2+"&authtype="+eds_authtype2+"&custid="+eds_custid2+"&groupid="+eds_groupid2+"&profile="+eds_profile2;
              }
              if (eds_authtype2 == 'uid') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&authtype="+eds_authtype2+"&user="+eds_user2+"&password="+eds_pass2+"&group="+eds_org2+"&profile="+eds_profile2+"&scope="+eds_scope2;
              }
              eds_url2 = eds_url2 + "&bquery=" + $("#searchBox").val();

              //console.log(eds_url2);
              $(location).attr('href',eds_url2);
              return false;
              break;
            case 'edsnative3':
              e.preventDefault();
              e.stopPropagation();
              var eds_url3 = $("input[name=exturl3]").val();

              var eds_authtype3 = $("input[name=eds_authtype3]").val();
              var eds_direct3 = $("input[name=eds_direct3]").val();
              var eds_catalogue_url3 = $("input[name=eds_catalogue_url3]").val();
              var eds_user3 = $("input[name=eds_user3]").val();
              var eds_pass3 = $("input[name=eds_pass3]").val();
              var eds_scope3 = $("input[name=eds_scope3]").val();
              var eds_profile3 = $("input[name=eds_profile3]").val();
              var eds_org3 = $("input[name=eds_org3]").val();
              var eds_custid3 = $("input[name=eds_custid3]").val();
              var eds_groupid3 = $("input[name=eds_groupid3]").val();
              var eds_site3 = $("input[name=eds_site3]").val();

              if (eds_authtype3 == 'athens') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&site="+eds_site3+"&authtype="+eds_authtype3+"&custid="+eds_custid3+"&groupid="+eds_groupid3+"&profile="+eds_profile3;
              }
              if (eds_authtype3 == 'sso') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&site="+eds_site3+"&authtype="+eds_authtype3+"&custid="+eds_custid3+"&groupid="+eds_groupid3+"&profile="+eds_profile3;
              }
              if (eds_authtype3 == 'ip,guest') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&site="+eds_site3+"&authtype="+eds_authtype3+"&custid="+eds_custid3+"&groupid="+eds_groupid3+"&profile="+eds_profile3;
              }
              if (eds_authtype3 == 'uid') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&authtype="+eds_authtype3+"&user="+eds_user3+"&password="+eds_pass3+"&group="+eds_org3+"&profile="+eds_profile3+"&scope="+eds_scope3;
              }
              eds_url3 = eds_url3 + "&bquery=" + $("#searchBox").val();

              //console.log(eds_url3);
              $(location).attr('href',eds_url3);
              return false;
              break;
            default:
              $("#searchBox").attr('name', 'query');
          }
        } else if ( $('.selectSearchCat').val() == 'ext3' ) {
          // external search (opac)
          $("input[name=edsurl3]").val('');
          var action = $("input[name=exturl3]").val();
          $("#globalSearch").attr("action", action);
          var type = $("input[name=exttype3]").val();
          switch(type) {
            case 'polaris':
              //$("#searchBox").name = 'term';
              $("#searchBox").attr('name', 'term');
              break;
            case 'sirsi':
              $("#searchBox").attr('name', 'qu');
              break;
            case 'iii':
              $("#searchBox").attr('name', 'target');
              break;
            case 'evergreen':
              $("#searchBox").attr('name', 'query');
              break;
            case 'oclc':
              $("#searchBox").attr('name', 'queryString');
              break;
            case 'koha':
              $("#searchBox").attr('name', 'q');
              break;
            case 'exlibris':
              $("#searchBox").attr('name', 'vl(freeText0)');
              break;
            case 'bibliocommons':
              $("#searchBox").attr('name', 'q');
              break;
            case 'vufind':
              $("#searchBox").attr('name', 'lookfor');
              break;
            case 'edsnative':
              e.preventDefault();
              e.stopPropagation();
              var eds_url = $("input[name=exturl3]").val();

              var eds_authtype = $("input[name=eds_authtype]").val();
              var eds_direct = $("input[name=eds_direct]").val();
              var eds_catalogue_url = $("input[name=eds_catalogue_url]").val();
              var eds_user = $("input[name=eds_user]").val();
              var eds_pass = $("input[name=eds_pass]").val();
              var eds_scope = $("input[name=eds_scope]").val();
              var eds_profile = $("input[name=eds_profile]").val();
              var eds_org = $("input[name=eds_org]").val();
              var eds_custid = $("input[name=eds_custid]").val();
              var eds_groupid = $("input[name=eds_groupid]").val();
              var eds_site = $("input[name=eds_site]").val();

              if (eds_authtype == 'athens') {
                eds_url = eds_url + "?direct="+eds_direct+"&site="+eds_site+"&authtype="+eds_authtype+"&custid="+eds_custid+"&groupid="+eds_groupid+"&profile="+eds_profile;
              }
              if (eds_authtype == 'sso') {
                eds_url = eds_url + "?direct="+eds_direct+"&site="+eds_site+"&authtype="+eds_authtype+"&custid="+eds_custid+"&groupid="+eds_groupid+"&profile="+eds_profile;
              }
              if (eds_authtype == 'ip,guest') {
                eds_url = eds_url + "?direct="+eds_direct+"&site="+eds_site+"&authtype="+eds_authtype+"&custid="+eds_custid+"&groupid="+eds_groupid+"&profile="+eds_profile;
              }
              if (eds_authtype == 'uid') {
                eds_url = eds_url + "?direct="+eds_direct+"&authtype="+eds_authtype+"&user="+eds_user+"&password="+eds_pass+"&group="+eds_org+"&profile="+eds_profile+"&scope="+eds_scope;
              }
              eds_url = eds_url + "&bquery=" + $("#searchBox").val();

              //console.log(eds_url);
              $(location).attr('href',eds_url);
              return false;
              break;
            case 'edsnative2':
              e.preventDefault();
              e.stopPropagation();
              var eds_url2 = $("input[name=exturl2]").val();

              var eds_authtype2 = $("input[name=eds_authtype2]").val();
              var eds_direct2 = $("input[name=eds_direct2]").val();
              var eds_catalogue_url2 = $("input[name=eds_catalogue_url2]").val();
              var eds_user2 = $("input[name=eds_user2]").val();
              var eds_pass2 = $("input[name=eds_pass2]").val();
              var eds_scope2 = $("input[name=eds_scope2]").val();
              var eds_profile2 = $("input[name=eds_profile2]").val();
              var eds_org2 = $("input[name=eds_org2]").val();
              var eds_custid2 = $("input[name=eds_custid2]").val();
              var eds_groupid2 = $("input[name=eds_groupid2]").val();
              var eds_site2 = $("input[name=eds_site2]").val();

              if (eds_authtype2 == 'athens') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&site="+eds_site2+"&authtype="+eds_authtype2+"&custid="+eds_custid2+"&groupid="+eds_groupid2+"&profile="+eds_profile2;
              }
              if (eds_authtype2 == 'sso') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&site="+eds_site2+"&authtype="+eds_authtype2+"&custid="+eds_custid2+"&groupid="+eds_groupid2+"&profile="+eds_profile2;
              }
              if (eds_authtype2 == 'ip,guest') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&site="+eds_site2+"&authtype="+eds_authtype2+"&custid="+eds_custid2+"&groupid="+eds_groupid2+"&profile="+eds_profile2;
              }
              if (eds_authtype2 == 'uid') {
                eds_url2 = eds_url2 + "?direct="+eds_direct2+"&authtype="+eds_authtype2+"&user="+eds_user2+"&password="+eds_pass2+"&group="+eds_org2+"&profile="+eds_profile2+"&scope="+eds_scope2;
              }
              eds_url2 = eds_url2 + "&bquery=" + $("#searchBox").val();

              //console.log(eds_url2);
              $(location).attr('href',eds_url2);
              return false;
              break;
            case 'edsnative3':
              e.preventDefault();
              e.stopPropagation();
              var eds_url3 = $("input[name=exturl3]").val();

              var eds_authtype3 = $("input[name=eds_authtype3]").val();
              var eds_direct3 = $("input[name=eds_direct3]").val();
              var eds_catalogue_url3 = $("input[name=eds_catalogue_url3]").val();
              var eds_user3 = $("input[name=eds_user3]").val();
              var eds_pass3 = $("input[name=eds_pass3]").val();
              var eds_scope3 = $("input[name=eds_scope3]").val();
              var eds_profile3 = $("input[name=eds_profile3]").val();
              var eds_org3 = $("input[name=eds_org3]").val();
              var eds_custid3 = $("input[name=eds_custid3]").val();
              var eds_groupid3 = $("input[name=eds_groupid3]").val();
              var eds_site3 = $("input[name=eds_site3]").val();

              if (eds_authtype3 == 'athens') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&site="+eds_site3+"&authtype="+eds_authtype3+"&custid="+eds_custid3+"&groupid="+eds_groupid3+"&profile="+eds_profile3;
              }
              if (eds_authtype3 == 'sso') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&site="+eds_site3+"&authtype="+eds_authtype3+"&custid="+eds_custid3+"&groupid="+eds_groupid3+"&profile="+eds_profile3;
              }
              if (eds_authtype3 == 'ip,guest') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&site="+eds_site3+"&authtype="+eds_authtype3+"&custid="+eds_custid3+"&groupid="+eds_groupid3+"&profile="+eds_profile3;
              }
              if (eds_authtype3 == 'uid') {
                eds_url3 = eds_url3 + "?direct="+eds_direct3+"&authtype="+eds_authtype3+"&user="+eds_user3+"&password="+eds_pass3+"&group="+eds_org3+"&profile="+eds_profile3+"&scope="+eds_scope3;
              }
              eds_url3 = eds_url3 + "&bquery=" + $("#searchBox").val();

              //console.log(eds_url3);
              $(location).attr('href',eds_url3);
              return false;
              break;
            default:
              $("#searchBox").attr('name', 'query');
          }
        } else if ( $('.selectSearchCat').val() == 'bento' ) {
          //Bento Search
          $("input[name=exturl]").val('');
          $("input[name=exturl2]").val('');
          $("input[name=exturl3]").val('');
          $("input[name=exttype]").val('');
          $("input[name=exttype2]").val('');
          $("input[name=exttype3]").val('');
          $("input[name=edsurl]").val('');
          $("input[name=web]").val('');
          
          var action = $("input[name=bento]").val();
          $("#globalSearch").attr("action", action);
          //$("#searchBox").name = 'query';
          $("#searchBox").attr('name', 'bentoq');
        } else if ($('.selectSearchCat').val() == 'web') {
          $("input[name=exturl]").val('');
          $("input[name=exturl2]").val('');
          $("input[name=exturl3]").val('');
          $("input[name=exttype]").val('');
          $("input[name=exttype2]").val('');
          $("input[name=exttype3]").val('');
          $("input[name=edsurl]").val('');
          $("input[name=bento]").val('');

          var action = $("input[name=web]").val();
          $("#globalSearch").attr("action", action);

          $("#searchBox").attr('name', 'bentoq');
        } else {
          // internal web search
          $("input[name=exturl]").val('');
          $("input[name=exturl2]").val('');
          $("input[name=exturl3]").val('');
          $("input[name=edsurl]").val('');
          $(this).action = '#';
          var searchText = $("#searchBox").val();
          window.location = basePath + "search/node/" + searchText;
          return false;

        }
      });
    }
  }
  
})(jQuery);
