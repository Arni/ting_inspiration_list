<?php

/**
 * @file
 * This plugin generates a inspiration list on a Inspiration list node. It's
 * mainly used to override the default page for this node type (node/%node).
 */
$plugin = array(
  'title' => t('Recommender service Cover list'),
  'description' => t('Show a list of relevant materials from reccomender service'),
  'single' => TRUE,
  'edit form' => 'ting_inspiration_list_rec_content_type_edit_form',
  'render callback' => 'ting_inspiration_list_rec_content_type_render',
  'category' => t('Ting'),
  //'required context' => array(new ctools_context_required(t('Inspiration List'), 'node')),
);

/**
 * Render the inspiration list block.
 */
function ting_inspiration_list_rec_content_type_render($subtype, $conf, $panel_args, $context) {
  // Define the return block.
  $block = new stdClass();
  
  //$ting_object_id = ting_adhl_get_id($contexts);
  //$result = ting_inspiration_list_search('holdingsitem.accessionDate>="NOW-100DAYS"', 'Nye materialer', 10); 
  
  $block->content = 'Test'; //$result;
  $path = drupal_get_path('module', 'ting_inspiration_list');
  drupal_add_css($path . '/css/ting_inspiration_list.css');
  drupal_add_js(drupal_get_path('module', 'ting_covers') . '/js/ting-covers.js');
  return $block;
}


/**
 * Enable admin settings page.
 */
function ting_inspiration_list_rec_content_type_edit_form($form, &$form_state) {
  return $form;
}

function ting_inspiration_list_get_id($contexts) {
// Get the objects to base the recommendation on based on the first supplied
// context
  $id = null;
  $ting_object_id = null;
  foreach ($contexts as $context) {
    $object = $context->get_original_argument();
    if ($object) {
      $id = $object->getId();
      break;
    }
  }
  if ($id) {
    $parts = explode(":", $id);
    if (isset($parts[1])) {
      $ting_object_id = $parts[1];
    }
  }
  return $ting_object_id;
}


