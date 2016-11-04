module.exports = function(grunt) {
  grunt.initConfig({
    theme_name: 'hfstacks', //Change this to your theme name
    pkg: grunt.file.readJSON('package.json'),

    sass: {
      options: {
        includePaths: [
          'bower_components/foundation/scss',
          'bower_components/components-font-awesome/scss'
        ]
      },
      dist: {
        options: {
          style: 'compressed',
          sourceMap: true
        },
        files: {
          '../../../modules/hf_stacks/hf_dashboard/css/hf_dashboard.css': 'scss/admin.scss',
          'css/palette_default.css': 'scss/default.scss',
          'css/palette_default_no_radius.css': 'scss/default-no-radius.scss',
          'css/palette_midnight_moon.css': 'scss/midnight-moon.scss',
          'css/palette_midnight_moon_no_radius.css': 'scss/midnight-moon-no-radius.scss',
          'css/palette_spring_breeze.css': 'scss/spring-breeze.scss',
          'css/palette_spring_breeze_no_radius.css': 'scss/spring-breeze-no-radius.scss',
          'css/palette_cool_steel.css': 'scss/cool-steel.scss',
          'css/palette_cool_steel_no_radius.css': 'scss/cool-steel-no-radius.scss',
          'css/maintenance.css': 'scss/admin/maintenance.scss'
        }
      },
      dev: {
        options: {
          style: 'compressed',
          sourceMap: true
        },
        files: {
          // 'admin/gallery/gallery.css': 'admin/gallery/gallery.scss',
          // '../../hf_adminimal/css/hf_adminimal.css': 'scss/admin/hf_adminimal.scss',
          // '../../../modules/hf_stacks/hf_dashboard/css/hf_dashboard.css': 'scss/admin.scss',
          'css/palette_default.css': 'scss/default.scss',
           //'css/maintenance.css': 'scss/admin/maintenance.scss',
           'css/palette_default_no_radius.css': 'scss/default-no-radius.scss',
           'css/palette_midnight_moon.css': 'scss/midnight-moon.scss',
           'css/palette_midnight_moon_no_radius.css': 'scss/midnight-moon-no-radius.scss',
           'css/palette_spring_breeze.css': 'scss/spring-breeze.scss',
           'css/palette_spring_breeze_no_radius.css': 'scss/spring-breeze-no-radius.scss',
           'css/palette_cool_steel.css': 'scss/cool-steel.scss',
           'css/palette_cool_steel_no_radius.css': 'scss/cool-steel-no-radius.scss'
        }
      },
      admin: {
        options: {
          style: 'compressed',
          sourcemap: 'inline'
        },
        files: {
          'admin_module/selecttheme/selecttheme.css': 'admin_module/selecttheme/selecttheme.scss',
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
        dest: 'js/app.js',
      },
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
        src: ['css/palette_default.css'],
        dest: 'css/ie9_default.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      default_no_radius: {
        src: ['css/palette_default_no_radius.css'],
        dest: 'css/ie9_default_no_radius.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      cool_steel: {
        src: ['css/palette_cool_steel.css'],
        dest: 'css/ie9_cool_steel.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      cool_steel_no_radius: {
        src: ['css/palette_cool_steel_no_radius.css'],
        dest: 'css/ie9_cool_steel_no_radius.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      midnight_moon: {
        src: ['css/palette_midnight_moon.css'],
        dest: 'css/ie9_midnight_moon.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      midnight_moon_no_radius: {
        src: ['css/palette_midnight_moon_no_radius.css'],
        dest: 'css/ie9_midnight_moon_no_radius.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      spring_breeze: {
        src: ['css/palette_spring_breeze.css'],
        dest: 'css/ie9_spring_breeze.css',
        options: { maxSelectors: 4095, maxPages: 3, suffix: '_page_' }
      },
      spring_breeze_no_radius: {
        src: ['css/palette_spring_breeze_no_radius.css'],
        dest: 'css/ie9_spring_breeze_no_radius.css',
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
        files: ['scss/**/*.scss', 'admin_module/**/*.scss'],
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

  grunt.registerTask('build', ['sass:dist', 'postcss', 'concat', 'csssplit']);
  grunt.registerTask('clean', ['sass:dev']);
  grunt.registerTask('default', ['watch']);
};
