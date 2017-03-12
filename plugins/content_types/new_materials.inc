<?php

/**
 * @file
 * This plugin generates a inspiration list on a Inspiration list node. It's
 * mainly used to override the default page for this node type (node/%node).
 */
$plugin = array(
  'title' => t('New materials Cover list'),
  'description' => t('Show a list of relevant materials'),
  'single' => TRUE,
  'edit form' => 'ting_inspiration_list_new_content_type_edit_form',
  'render callback' => 'ting_inspiration_list_new_content_type_render',
  'category' => t('Ting'),
  //'required context' => array(new ctools_context_required(t('Inspiration List'), 'node')),
);

/**
 * Render the inspiration list block.
 */
function ting_inspiration_list_new_content_type_render($subtype, $conf, $panel_args, $context) {
  // Define the return block.
  $block = new stdClass();
  $result = ting_inspiration_list_search('holdingsitem.accessionDate>="NOW-100DAYS"', 'Nye materialer', 10); 
  
  $block->content = $result;
  $path = drupal_get_path('module', 'ting_inspiration_list');
  drupal_add_css($path . '/css/ting_inspiration_list.css');
  drupal_add_js(drupal_get_path('module', 'ting_covers') . '/js/ting-covers.js');
  return $block;
}


/**
 * Enable admin settings page.
 */
function ting_inspiration_list_new_content_type_edit_form($form, &$form_state) {
  return $form;
}



