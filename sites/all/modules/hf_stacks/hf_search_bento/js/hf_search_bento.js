/**
 * HF_Search_Bento Javascript
 *
 * Responsible for creating ajax calls based on the given query and the configuration
 * settings of the Bento box search.
 */
(function ($, Drupal) {

    /**
     * Main Body
     * @type {{attach: Drupal.behaviors.hf_search_bento.attach}}
     */
    Drupal.behaviors.hf_search_bento = {
        attach: function (context, settings) {
            //Div Container to hold results brought back from AJAX
            var resultContainer = $('.ajaxResult');
            //Retrieve variables passed from the Drupal Bento Module
            if(settings.hf_search_bento){
                var names = settings.hf_search_bento.names;
                var delta = settings.hf_search_bento.delta;
                var limit = settings.hf_search_bento.limit;
                var query = settings.hf_search_bento.query;
                var platformType = settings.hf_search_bento.platform;
            }

            //Check to see if resultContainer has class "appended"
            if(!resultContainer.hasClass("appended")) {
                //Check to see if the container does exist
                if(resultContainer.length > 0) {
                    //For each container perform the AJAX call and add "appended" to the resultContainer's class
                    resultContainer.each(function(i){
                        searchEDS(query, names[i], delta[i], limit[i], platformType[i]);
                        resultContainer.addClass("appended");
                    });
                }
            }
        }
    };

    /**
     * Calls the AJAX function (eds_ajax_call) within the main module file of Search Bento
     *
     * @param {string} query        The entered search query extracted from the url.
     * @param {string} sourceType   The source type retrieved from the configuration setting array, e.g. Books, Academic Journals, etc.
     * @param {string} divName      The generated name of the DIV (e.g., "ajax-[sourceType]") that corresponds to the generated DIV in the tpl file.
     * @param {int}    limit        The display limit set for each ajax block.
     */
    function searchEDS(query, sourceType, delta, limit, platformType ) {
        var html = "";
        delta = delta.replace(" ", "-");
        //The DIV with the uniquely generated divName corresponding the block
        var divContainer = $('#' + 'ajax' + delta);
        //Container for the seeMore Button
        var seeMoreID = "#seeMoreButton" + sourceType.replace(" ", "-");
        seeMoreID = seeMoreID.replace("&", "\\&");
        //Hide Container initially
        $(seeMoreID).hide();

        //The URL that calls the AJAX function in the module file
        var requestUrl = Drupal.settings.basePath + 'searchbento/eds';

        if (sourceType == 'Everything') {
            sourceType = '';
        }

        /**
         * AJAX Call to the Drupal Function
         * @param {string} query        The entered search query extracted from the url.
         * @param {string} sourceType   The sourceType desired.
         */
        $.get(requestUrl, {query: query, source: sourceType, platformType: platformType, delta: delta, limit: limit})
            .done(function(data) {
                platformType = parseInt(platformType);
                switch(platformType) {
                    /**
                     * EDS
                     */
                    case 2:
                        if(data['records'].length > 0) {

                            $.each(data, function(key, value) {
                                //Start building the html for each result set
                                html += "<div class='bnt-result'>";
                                //Build html for each item in result set
                                $.each(value, function(i, result) {

                                    var param = result.record_id.split("|");
                                    var an = param[0];
                                    var db = param[1];
                                    html += "<div class='bnt-result-item row'>";
                                    if(result.iconcover != "") {
                                        coverimage = result.iconcover;
                                        html += "<div class='small-3 medium-2 large-2 columns cover text-center'>" + coverimage + "</div>";
                                    }
                                    html += "<div class='small-6 medium-5 large-8 columns'>";
                                    html += "<h5 class='bnt-item-ttl'><a href='/eds/detail?db=" + db + "&an=" + an + "'>";
                                    //console.log(result);

                                    if (result.title != "") {
                                        html += result.title;
                                    } else {
                                        html += "Title is not available";
                                    }

                                    html += "</a></h5>";
                                    if(result.authors != "") {
                                        html += "<p class='authors'><strong>Authors:</strong> " + result.authors + "</h3></p>";
                                    }
                                    if(result.summary != "") {
                                        html += "<p class='summary'>" + truncate.apply(result.summary, [150, false]) + "</p>";
                                    }
                                    html += "</div>";
                                    html += "<div class='small-3 medium-3 large-2 columns text-center'>";

                                    var readonline = false;
                                    if (typeof(result.items.URL) === 'object') {
                                        var linkUrl = result.items.URL.Data;
                                        if (linkUrl.indexOf("href") != -1) {
                                            linkUrl = $(linkUrl).attr("href");
                                        }
                                        html += '<a href="'+linkUrl+'" class="button bentoRead" target="_blank">Read Online</a>';
                                        readonline = true;
                                    }
                                    if (readonline == false) {
                                        if (typeof(result.extra_links[0]) === 'object') {
                                            //console.log(result.extra_links);
                                            $.each(result.extra_links, function (i, linker) {
                                                link = linker.Url;
                                                linkStatus = link.indexOf('tind.io') !== -1;
                                                // display place request button only if url doesn't contain "tind.io"
                                                if (linkStatus == true) {
                                                    html += '<a href="'+linker.Url+'" class="button bentoHold" target="_blank">Place Request</a>';
                                                }
                                            });

                                        }
                                    }
                                    html += "</div></div>";

                                });
                                html += "</div>";
                            });

                            //If the result count is greater than the limit, append the count of results and show the seeMore button.
                            if(data['count'] > limit) {
                                $(seeMoreID).append(" (" + data['count'] + ")");
                                $(seeMoreID).show();
                            }

                            //Append created html to the DIVContainer
                            divContainer.find(".bnt-content").append(html);

                            //Edit the href to go to the search page with current parameters
                            //console.log(sourceType);
                            if(sourceType == '') {
                                divContainer.find("#seeMoreButtonEverything").attr("href", Drupal.settings.basePath + "eds?query=" + query);
                            } else if (sourceType == "Audio-Visual") {
                                divContainer.find("#seeMoreButtonAudio-Visual").attr("href", Drupal.settings.basePath + "eds?query=" + query + "&ff[]=SourceType:Audio&ff[]=SourceType:Videos");
                            } else if (sourceType == "Books & eBooks") {
                                divContainer.find("#seeMoreButtonBooks-\\&-eBooks").attr("href", Drupal.settings.basePath + "eds?query=" + query + "&ff[]=SourceType:Books&ff[]=SourceType:eBooks");
                            } else if (sourceType == "Everything Else") {
                                divContainer.find("#seeMoreButtonEverything-Else").attr("href", Drupal.settings.basePath + "eds?query=" + query + "&ff[]=SourceType:Electronic Resources&ff[]=SourceType:Magazines&ff[]=SourceType:Reviews&ff[]=SourceType:Reports&ff[]=SourceType:News&ff[]=SourceType:Conference Materials&ff[]=SourceType:Non-Print Resources&ff[]=SourceType:Dissertations&ff[]=SourceType:Music Scores&ff[]=SourceType:Primary Source Documents&ff[]=SourceType:Biographies");
                            } else {
                                divContainer.find("#seeMoreButton" + sourceType.replace(" ", "-")).attr("href", Drupal.settings.basePath + "eds?query=" + query + "&ff[]=SourceType:" + sourceType.replace(/ /g, '+'));
                            }

                            //Empty the loader GIF
                            $('.ajax-loader').empty();

                            //Correct appropriate href link for each Author to direct to Jasen's search page
                            $('.authors').each(function(index, element) {
                                var anchor = $(this).find("a");
                                anchor.each(function(index, element) {
                                    $(this).attr("href", Drupal.settings.basePath + "eds?query=" + ($(this).text()).replace(/[\. ,:-]+/g, '+') + "&type=AR");
                                });
                            });
                        } else {
                            //When no results are returned
                            html += "<div class='bnt-no-result'>";
                            html += "<p>No results found.</p>";
                            html += "</div>";

                            $(seeMoreID).hide();
                            divContainer.find(".bnt-content").append(html);
                            //Empty the loader GIF
                            $('.ajax-loader').empty();
                        }
                        break;
                    /**
                     * Polaris
                     */
                    case 3:
                        if(data.records.length > 0 && data.records != null) {
                            //$.each(data.records, function(key, value) {
                            //Build HTML output for Polaris Results
                            html += "<div class='bnt-result'>";
                            $.each(data.records, function (i, result) {
                                html += "<div class='bnt-result-item'>";
                                html += "<h5 class='bnt-item-ttl'><a href='"+ data.url + "/title.aspx?cn=" + result.ControlNumber + "'>" + result.Title + "</a></h5>";
                                //html += "<h5 class='bnt-item-ttl'><a href='"+ data.url + "'>" + result.Title + "</a></h5>";
                                if (result.Author != "") {
                                    html += "<p class='authors'><strong>Authors:</strong> " + result.Author + "</h3></p>";
                                }
                                if (result.Summary != "") {
                                    html += "<p class='summary'>" + truncate.apply(result.Summary, [150, false]) + "</p>";
                                }
                                html += "</div>";
                            });
                            html += "</div>";
                            //});

                            //If the result count is greater than the limit, append the count of results and show the seeMore button.
                            if(data.count > limit) {
                                $(seeMoreID).append(" (" + data['count'] + ")");
                                $(seeMoreID).show();
                            }

                            //Append created html to the DIVContainer
                            divContainer.find(".bnt-content").append(html);
                            //Edit the href to go to Jasen's search page with current parameters
                            //divContainer.find("#seeMoreButton" + sourceType.replace(" ", "-")).attr("href", Drupal.settings.basePath + "eds?query=" + query + "&ff[]=SourceType:" + sourceType.replace(/ /g, '+'));

                            //Empty the loader GIF
                            $('.ajax-loader').empty();
                        } else {
                            //When no results are returned
                            html += "<div class='bnt-no-result'>";
                            html += "<p>No results found.</p>";
                            html += "</div>";

                            $(seeMoreID).hide();
                            divContainer.find(".bnt-content").append(html);
                            //Empty the loader GIF
                            $('.ajax-loader').empty();
                        }
                        break;
                    /**
                     * Sirsi
                     */
                    case 4:
                        if(data.HitlistTitleInfo.length > 0) {
                            html += "<div class='bnt-result'>";
                            $.each(data.HitlistTitleInfo, function (i, result) {
                                //console.log(result);
                                html += "<div class='bnt-result-item'>";
                                html += "<h5 class='bnt-item-ttl'><a href='#'>" + result.title + "</a></h5>";
                                if (result.author != "") {
                                    html += "<p class='authors'><strong>Authors:</strong> " + result.author+ "</h3></p>";
                                }
                                if (result.materialType != "") {
                                    html += "<p class='summary'><strong>Material Type: </strong>" + result.materialType + "</p>";
                                }
                                html += "</div>";
                            });
                            html += "</div>";

                            //If the result count is greater than the limit, append the count of results and show the seeMore button.
                            if(parseInt(data.totalHits) > limit) {
                                $(seeMoreID).append(" (" + data.totalHits + ")");
                                $(seeMoreID).show();
                            }
                            //Append created html to the DIVContainer
                            divContainer.find(".bnt-content").append(html);
                            //Edit the href to go to Jasen's search page with current parameters
                            //divContainer.find("#seeMoreButton" + sourceType.replace(" ", "-")).attr("href", Drupal.settings.basePath + "eds?query=" + query + "&ff[]=SourceType:" + sourceType.replace(/ /g, '+'));

                            //Empty the loader GIF
                            $('.ajax-loader').empty();
                        } else {
                            //When no results are returned
                            html += "<div class='bnt-no-result'>";
                            html += "<p>No results found.</p>";
                            html += "</div>";

                            $(seeMoreID).hide();
                            divContainer.find(".bnt-content").append(html);
                            //Empty the loader GIF
                            $('.ajax-loader').empty();
                        }
                        break;
                    /**
                     * Ebsco Publications
                     */
                    case 5:
                        if(data['records'].length > 0) {
                            $.each(data, function(key, value) {
                                //Start building the html for each result set
                                html += "<div class='bnt-result'>";
                                //Build html for each item in result set
                                $.each(value, function(i, result) {
                                    var url = result.full_text.URL;
                                    var sid = result.sid;
                                    html += "<div class='bnt-result-item'>";
                                    //html += "<h5 class='bnt-item-ttl'><a href='/eds/detail?db=" + db + "&an=" + an + "'>" + result.title + "</a></h5>";
                                    html += "<h5 class='bnt-item-ttl'><a href='http://eds.a.ebscohost.com/eds/ExternalLinkOut/PubFinderLinkOut?sid=" + sid + "&Url=" + url + "' target='_blank'>" + result.title + "</a></h5>";

                                    if(result.authors != "") {
                                        html += "<p class='authors'><strong>Authors:</strong> " + result.authors + "</h3></p>";
                                    }
                                    if(result.summary != "") {
                                        html += "<p class='summary'>" + truncate.apply(result.summary, [150, false]) + "</p>";
                                    }
                                    html += "</div>";
                                });
                                html += "</div>";
                            });

                            //If the result count is greater than the limit, append the count of results and show the seeMore button.
                            if(data['count'] > limit) {
                                $(seeMoreID).append(" (" + data['count'] + ")");
                                $(seeMoreID).show();
                            }

                            //Append created html to the DIVContainer
                            divContainer.find(".bnt-content").append(html);

                            //Empty the loader GIF
                            $('.ajax-loader').empty();

                            //Correct appropriate href link for each Author to direct to Jasen's search page
                            $('.authors').each(function(index, element) {
                                var anchor = $(this).find("a");
                                anchor.each(function(index, element) {
                                    $(this).attr("href", Drupal.settings.basePath + "eds?query=" + ($(this).text()).replace(/[\. ,:-]+/g, '+') + "&type=AR");
                                });
                            });
                        } else {
                            //When no results are returned
                            html += "<div class='bnt-no-result'>";
                            html += "<p>No results found.</p>";
                            html += "</div>";

                            $(seeMoreID).hide();
                            divContainer.find(".bnt-content").append(html);
                            //Empty the loader GIF
                            $('.ajax-loader').empty();
                        }
                        break;
                    default:
                        //When no results are returned
                        html += "<div class='bnt-no-result'>";
                        html += "<p>No results found.</p>";
                        html += "</div>";

                        $(seeMoreID).hide();
                        divContainer.find(".bnt-content").append(html);
                        //Empty the loader GIF
                        $('.ajax-loader').empty();
                        break;
                }
            })
            //If HTTP Error Code has been returned.
            .fail(function() {
                //When no results are returned
                html += "<div class='bnt-no-result'>";
                html += "<p>Error loading results, please check proper EDS/ILS credentials have been entered.</p>";
                html += "</div>";

                $(seeMoreID).hide();
                divContainer.find(".bnt-content").append(html);
                //Empty the loader GIF
                $('.ajax-loader').empty();
            });
    }

    /**
     * This function truncates the specified string based on inputted character limit.
     *
     * @param {string}     n                     The string to be truncated.
     * @param {string}     useWordBoundary       The character limit.
     * @returns {string}    The truncated string.
     */
    function truncate( n, useWordBoundary ){
        var isTooLong = this.length > n,
            s_ = isTooLong ? this.substr(0,n-1) : this;
        s_ = (useWordBoundary && isTooLong) ? s_.substr(0,s_.lastIndexOf(' ')) : s_;
        return  isTooLong ? s_ + '&hellip;' : s_;
    }
})(jQuery, Drupal);