module.exports = function(grunt) {
  grunt.initConfig({
    theme_name: 'crayons', //Change this to your theme name
    pkg: grunt.file.readJSON('package.json'),

    sass: {
      options: {
        includePaths: [
          './../../hfstacks/assets/bower_components/foundation/scss',
          './../../hfstacks/assets/bower_components/components-font-awesome/scss'
        ],
      },
      dist: {
        options: {
          style: 'compressed',
          sourceMap: true
        },
        files: {
          'css/palette_crayons.css': 'scss/crayons.scss',
        }
      },
      dev: {
        options: {
          style: 'compressed',
          sourceMap: true
        },
        files: {
          'css/palette_crayons.css': 'scss/crayons.scss',
        }
      },
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
        src: ['js/modules/*.js'],
        dest: 'js/crayons.js',
      },
    },

    uglify: {
      my_target: {
        options: {
          mangle: false
        },
        files: {
          'js/crayons.min.js': 'js/crayons.js'
        }
      }
    },

    csssplit: {
      default: {
        src: ['css/palette_crayons.css'],
        dest: 'css/ie9_crayons.css',
        options: { maxSelectors: 4090, maxPages: 3, suffix: '_page_' }
      },
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
        files: ['scss/**/*.scss'],
        tasks: ['sass:dev'],
        options: {
          livereload: false
        }
      },
      scripts: {
        files: ['js/**/*.js'],
        tasks: ['concat'],
        options: {
          spawn: false,
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
  grunt.registerTask('drushit', ['drush']);
  grunt.registerTask('default', ['watch']);
};
