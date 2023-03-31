# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

from sphinx.builders.html import StandaloneHTMLBuilder
import subprocess, os

# Doxygen
subprocess.call('doxygen ../Doxyfile.in', shell=True)

project = 'HAB-SEDS-TTU'
copyright = '2023, William Stump, Chris Swindell, Luke Chapman, Emma Krebs, Mia Guzman'
author = 'William Stump, Chris Swindell, Luke Chapman, Emma Krebs, Mia Guzman'
release = '0.1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['sphinx.ext.todo',
              'breathe']

templates_path = ['_templates']
exclude_patterns = ['doxygen_docs', 'build']
highlight_language = 'c++'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'scrolls'
html_static_path = ['_static']

# Breath configuration
breathe_projects = {
    'HAB-SEDS-TTU': 'doxygen_docs/xml'
}
#breathe_projects_source = {
#    'auto': ('../doxygen_docs/xml', ['main_8cpp.xml'])
#}
breathe_default_project = 'HAB-SEDS-TTU'
breathe_default_members = ('members', 'undoc-members')
