module.exports = function (grunt) {
  grunt.initConfig({
    theme_name: 'catarina', //Change this to your theme name
    pkg: grunt.file.readJSON('package.json'),

    sass: {
      options: {
        sourceMap: true,
        includePaths: [
          './../../hfstacks/assets/bower_components/foundation/scss'
        ]
      },
      dist: {
        options: {
          style: 'compressed',
          sourcemap: 'inline'
        },
        files: {
          'css/palette_autumn_mist.css': 'scss/autumn_mist.scss',
          'css/palette_back_to_school.css': 'scss/back_to_school.scss',
          'css/palette_bare_essentials.css': 'scss/bare_essentials.scss',
          'css/palette_classy_casual.css': 'scss/classy_casual.scss',
          'css/palette_calm_concrete.css': 'scss/calm_concrete.scss',
          'css/palette_catarina.css': 'scss/catarina.scss',
          'css/palette_dragon_fire.css': 'scss/dragon_fire.scss',
          'css/palette_drift_wood.css': 'scss/drift_wood.scss',
          'css/palette_great_white.css': 'scss/great_white.scss',
          'css/palette_lady_business.css': 'scss/lady_business.scss',
          'css/palette_mountain_sunset.css': 'scss/mountain_sunset.scss',
          'css/palette_night_frost.css': 'scss/night_frost.scss',
          'css/palette_summer_lawn.css': 'scss/summer_lawn.scss',
          'css/palette_sweet_sugar.css': 'scss/sweet_sugar.scss',
          'css/palette_time_travel.css': 'scss/time_travel.scss',
          'css/palette_the_reef.css': 'scss/the_reef.scss',
          'css/palette_tropical_swell.css': 'scss/tropical_swell.scss',
          'css/palette_urban_skyline.css': 'scss/urban_skyline.scss'
        }
      },
      dev: {
        options: {
          style: 'compressed',
          sourcemap: 'inline'
        },
        files: {
          // 'css/palette_autumn_mist.css': 'scss/autumn_mist.scss',
          // 'css/palette_back_to_school.css': 'scss/back_to_school.scss',
           'css/palette_bare_essentials.css': 'scss/bare_essentials.scss',
          // 'css/palette_classy_casual.css': 'scss/classy_casual.scss',
          // 'css/palette_calm_concrete.css': 'scss/calm_concrete.scss',
          // 'css/palette_catarina.css': 'scss/catarina.scss', // Corporate Keener
          // 'css/palette_dragon_fire.css': 'scss/dragon_fire.scss',
          'css/palette_drift_wood.css': 'scss/drift_wood.scss',
          // 'css/palette_great_white.css': 'scss/great_white.scss',
          // 'css/palette_lady_business.css': 'scss/lady_business.scss',
          // 'css/palette_mountain_sunset.css': 'scss/mountain_sunset.scss',
          // 'css/palette_night_frost.css': 'scss/night_frost.scss',
          // 'css/palette_summer_lawn.css': 'scss/summer_lawn.scss',
          // 'css/palette_sweet_sugar.css': 'scss/sweet_sugar.scss',
          // 'css/palette_time_travel.css': 'scss/time_travel.scss',
          // 'css/palette_the_reef.css': 'scss/the_reef.scss',
          // 'css/palette_tropical_swell.css': 'scss/tropical_swell.scss',
          'css/palette_urban_skyline.css': 'scss/urban_skyline.scss'
        }
      }
    },

    postcss: {
      options: {
        map: true,
        processors: [
          require('autoprefixer-core')({browsers: 'last 4 version'}),
          require('csswring')
        ]
      },
      dist: {
        src: 'css/*.css'
      }
    },

    concat: {
      options: {
        separator: '\n\n',
        banner: '(function ($, Drupal) { Drupal.behaviors.<%= theme_name %> = { attach: function(context, settings) {\nvar basePath = Drupal.settings.basePath;\nvar pathToTheme = Drupal.settings.pathToTheme;\n\n',
        footer: '\n\n}};})(jQuery, Drupal);'
      },
      dist: {
        src: 'js/modules/*.js',
        dest: 'js/catarina.js'
      }
    },

    uglify: {
      my_target: {
        options: {
          mangle: false
        },
        files: {
          'js/app.min.js': 'js/app.js'
        }
      }
    },

    csssplit: {
      autumn_mist: {
        src: ['css/palette_autumn_mist.css'],
        dest: 'css/ie9_autumn_mist.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      back_to_school: {
        src: ['css/palette_back_to_school.css'],
        dest: 'css/ie9_back_to_school.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      bare_essentials: {
        src: ['css/palette_bare_essentials.css'],
        dest: 'css/ie9_bare_essentials.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      calm_concrete: {
        src: ['css/palette_calm_concrete.css'],
        dest: 'css/ie9_calm_concrete.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      classy_casual: {
        src: ['css/palette_classy_casual.css'],
        dest: 'css/ie9_classy_casual.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      // default == Corporate Keener
      default: {
        src: ['css/palette_catarina.css'],
        dest: 'css/ie9_catarina.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      dragon_fire: {
        src: ['css/palette_dragon_fire.css'],
        dest: 'css/ie9_dragon_fire.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      drift_wood: {
        src: ['css/palette_drift_wood.css'],
        dest: 'css/ie9_drift_wood.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      great_white: {
        src: ['css/palette_great_white.css'],
        dest: 'css/ie9_great_white.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      lady_business: {
        src: ['css/palette_lady_business.css'],
        dest: 'css/ie9_lady_business.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      mountain_sunset: {
        src: ['css/palette_mountain_sunset.css'],
        dest: 'css/ie9_mountain_sunset.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      night_frost: {
        src: ['css/palette_night_frost.css'],
        dest: 'css/ie9_night_frost.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      summer_lawn: {
        src: ['css/palette_summer_lawn.css'],
        dest: 'css/ie9_summer_lawn.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      sweet_sugar: {
        src: ['css/palette_sweet_sugar.css'],
        dest: 'css/ie9_sweet_sugar.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      time_travel: {
        src: ['css/palette_time_travel.css'],
        dest: 'css/ie9_time_travel.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      the_reef: {
        src: ['css/palette_the_reef.css'],
        dest: 'css/ie9_the_reef.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      tropical_swell: {
        src: ['css/palette_tropical_swell.css'],
        dest: 'css/ie9_tropical_swell.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      urban_skyline: {
        src: ['css/palette_urban_skyline.css'],
        dest: 'css/ie9_urban_skyline.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      }
    },

    drush: {
      cc_registry: {
        args: ['cc', 'all']
      }
     },

    watch: {
      options: { reload: true },
      grunt: { files: ['Gruntfile.js'] },
      sass: {
        files: 'scss/**/*.scss',
        tasks: ['sass:dev'],
        options: {
          livereload: true
        }
      },
      scripts: {
        files: ['js/**/*.js'],
        tasks: ['concat'],
        options: {
          spawn: true
        }
      }
    }
  });

  grunt.loadNpmTasks('grunt-sass');
  grunt.loadNpmTasks('grunt-postcss');
  grunt.loadNpmTasks('grunt-drush');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-concat');
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-csssplit');

  grunt.registerTask('build', ['sass:dist', 'postcss:dist', 'concat', 'csssplit']);
  grunt.registerTask('clean', ['sass:dev']);
  grunt.registerTask('default', ['watch']);
};