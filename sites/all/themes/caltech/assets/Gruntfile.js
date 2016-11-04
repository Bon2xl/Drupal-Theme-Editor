module.exports = function (grunt) {
  grunt.initConfig({
    theme_name: 'caltech', //Change this to your theme name
    pkg: grunt.file.readJSON('package.json'),

    sass: {
      options: {
        includePaths: [
          './../../hfstacks/assets/bower_components/foundation/scss'
        ]
      },
      dist: {
        options: {
          style: 'compressed',
          sourceMap: true
        },
        files: {
          'css/palette_caltech.css': 'scss/caltech.scss',
        }
      },
      dev: {
        options: {
          style: 'compressed',
          sourceMap: true
        },
        files: {
          'css/palette_caltech.css': 'scss/caltech.scss',
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
        footer: '\n\n}};})(jQuery, Drupal);',
      },
      dist: {
        src: 'js/modules/*.js',
        dest: 'js/caltech.js',
      },
    },

    uglify: {
      my_target: {
        options: {
          mangle: false
        },
        files: {
          'js/caltech.min.js': 'js/caltech.js'
        }
      }
    },

    csssplit: {
      default: {
        src: ['css/palette_caltech.css'],
        dest: 'css/ie9_caltech.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
    },

    drush: {
      cc_registry: {
        args: ['cc', 'all']
      }
     },

    watch: {
      options: { reload: false },
      grunt: { files: ['Gruntfile.js'] },
      sass: {
        files: 'scss/**/*.scss',
        tasks: ['sass:dev'],
      },
      scripts: {
        files: ['js/modules/*.js'],
        tasks: ['concat:dist'],
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
  grunt.registerTask('default', ['watch']);
};
