module.exports = function (grunt) {
  grunt.initConfig({
    theme_name: 'metals', //Change this to your theme name
    pkg: grunt.file.readJSON('package.json'),

    sass: {
      options: {
        includePaths: [
          './../../hfstacks/assets/bower_components/foundation/scss',
          './../../hfstacks/assets/bower_components/components-font-awesome/scss'
        ]
      },
      dist: {
        options: {
          style: 'compressed',
          sourcemap: 'inline'
        },
        files: {
          'css/palette_nickel.css': 'scss/nickel.scss',
          'css/palette_steel.css': 'scss/steel.scss',
          'css/palette_bronze.css': 'scss/bronze.scss',
          'css/palette_silver.css': 'scss/silver.scss',
          'css/palette_gold.css': 'scss/gold.scss',
          'css/palette_metals.css': 'scss/metals.scss', // default 'iron'
        }
      },
      dev: {
        options: {
          style: 'compressed',
          sourcemap: 'inline'
        },
        files: {
          // 'css/palette_nickel.css': 'scss/nickel.scss',
          // 'css/palette_steel.css': 'scss/steel.scss',
          // 'css/palette_bronze.css': 'scss/bronze.scss',
          // 'css/palette_silver.css': 'scss/silver.scss',
          // 'css/palette_gold.css': 'scss/gold.scss',
          'css/palette_metals.css': 'scss/metals.scss',
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
        dest: 'js/metals.js'
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
      default: {
        src: ['css/palette_metals.css'],
        dest: 'css/ie9_metals.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      metals_bronze: {
        src: ['css/palette_metals_bronze.css'],
        dest: 'css/ie9_metals_bronze.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      metals_gold: {
        src: ['css/palette_metals_gold.css'],
        dest: 'css/ie9_metals_gold.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      metals_nickle: {
        src: ['css/palette_metals_nickle.css'],
        dest: 'css/ie9_metals_nickle.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      metals_silver: {
        src: ['css/palette_silver.css'],
        dest: 'css/ie9_met_silver.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      metals_steel: {
        src: ['css/palette_steel.css'],
        dest: 'css/ie9_met_steel.css',
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
        tasks: ['sass:dev', 'csssplit:default'],
        options: {
          livereload: false
        }
      },
      scripts: {
        files: ['js/**/*.js'],
        tasks: ['concat'],
        options: {
          spawn: false
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
