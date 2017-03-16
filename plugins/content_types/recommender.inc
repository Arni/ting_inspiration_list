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
  $path = explode('/', current_path()); 
  $id = $path[2]; 
  
  ting_inspiration_list_set_cookie($id);
  $result = ting_open_platform_recommender(array($id),15);
  file_put_contents("/var/www/drupalvm/drupal/debug/path.txt", print_r($id  , TRUE), FILE_APPEND);
  file_put_contents("/var/www/drupalvm/drupal/debug/recom.txt", print_r($result  , TRUE), FILE_APPEND);
  $block->content = ting_inspiration_list_render_recommendations("Anbefalinger", $result->data);
  //$block->content = 'Test'; //$result;
  $path = drupal_get_path('module', 'ting_inspiration_list');
  drupal_add_css($path . '/css/ting_inspiration_list.css');
  drupal_add_js(drupal_get_path('module', 'ting_covers') . '/js/ting-covers.js');
  return $block;
}


function ting_inspiration_list_set_cookie($id) {
  if (isset($_COOKIE['ting_inspiration_list_objects'])) {
    $json = $_COOKIE['ting_inspiration_list_objects'];
    $objects = json_decode($json);
    if (count($objects) >= 5) {
      array_shift($objects);
    }
    $objects[] = $id;
    $json = json_encode($objects);
    setcookie('ting_inspiration_list_objects', $json, time()+ 2000000, '/');
  } else {
    $json = json_encode(array($id));
    setcookie('ting_inspiration_list_objects', $json, time()+ 2000000, '/');
  }
}

/**
 * Enable admin settings page.
 */
function ting_inspiration_list_rec_content_type_edit_form($form, &$form_state) {
  return $form;
}





