<?php
/**
 * @file
 * fblog.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function _fblog_get_taxonomy_vocabularies() {
  return array(
    'fblog_category' => array(
      'name' => 'Blog Category',
      'machine_name' => 'fblog_category',
      'description' => 'For blog',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'fblog_tags' => array(
      'name' => 'Blog Tags',
      'machine_name' => 'fblog_tags',
      'description' => 'Use tags to group articles on similar topics into categories.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
