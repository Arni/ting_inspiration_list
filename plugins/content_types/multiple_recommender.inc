<?php

/**
 * @file
 * This plugin generates a inspiration list on a Inspiration list node. It's
 * mainly used to override the default page for this node type (node/%node).
 */
$plugin = array(
  'title' => t('Multiple Recommender service Cover list'),
  'description' => t('Show a list of relevant materials from reccomender service based on objects looked at'),
  'single' => TRUE,
  'edit form' => 'ting_inspiration_list_multi_content_type_edit_form',
  'render callback' => 'ting_inspiration_list_multi_content_type_render',
  'category' => t('Ting'),
  //'required context' => array(new ctools_context_required(t('Inspiration List'), 'node')),
);

/**
 * Render the inspiration list block.
 */
function ting_inspiration_list_multi_content_type_render($subtype, $conf, $panel_args, $context) {
  // Define the return block.
  $block = new stdClass();
  if (isset($_COOKIE['ting_inspiration_list_objects'])) {
    $json = $_COOKIE['ting_inspiration_list_objects'];
    $objects  = json_decode($json);
  } else {
    $objects = array('870970-basis:50798437', '870970-basis:50587282', '870970-basis:29955530', '870970-basis:29953554', '870970-basis:50507319');
  }
  $result = ting_open_platform_recommender($objects, 15);

  file_put_contents("/var/www/drupalvm/drupal/debug/recom.txt", print_r($result, TRUE), FILE_APPEND);
  $block->content = ting_inspiration_list_render_recommendations("Anbefalet til dig", $result->data);

  $path = drupal_get_path('module', 'ting_inspiration_list');
  drupal_add_css($path . '/css/ting_inspiration_list.css');
  drupal_add_js(drupal_get_path('module', 'ting_covers') . '/js/ting-covers.js');
  return $block;
}

/**
 * Enable admin settings page.
 */
function ting_inspiration_list_multi_content_type_edit_form($form, &$form_state) {
  return $form;
}





