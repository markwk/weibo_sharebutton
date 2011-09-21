<?php

/**
 * @file
 * Administration page for the Weibo Share Button
 */

/**
 * Menu callback: displays the Weibo Share Button module settings page.
 *
 * @ingroup forms
 */
function weibo_sharebutton_admin_settings() {
	$script = '';
	drupal_set_html_head('');
	
	$locations = array(
		'full' => t('Full node'),
	    'teaser' => t('Teaser'),
	    'link' => t('Node links'),
	  );

	$form['display'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Display Settings'),
	    '#description' => t('These are settings for nodes: the button will be created dynamically for each node using its URL. <br />On the other hand, if you only need a block with a fixed URL like your homepage, go to the <a href="@blocks">blocks</a> page to enable and configure the <em>Weibo Share Button</em> block.', array('@blocks' => url('admin/build/block'))),
	  );

	  $form['display']['weibo_sharebutton_appkey'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Sina Weibo App Key'),
	    '#maxlength' => 256,
	    '#default_value' => variable_get('weibo_sharebutton_appkey', ''),
	    '#description' => t('You can get Sina Weibo App Key at <a href="http://open.sina.com">Open Sina</a>.'),
	  );
	
	$form['display']['weibo_sharebutton_node_types'] = array(
	    '#type' => 'checkboxes',
	    '#title' => t('Display the button on these content types:'),
	    '#options' => node_get_types('names'),
	    '#default_value' => variable_get('weibo_sharebutton_node_types', array()),
	  );

	  $form['display']['weibo_sharebutton_node_location'] = array(
	    '#type' => 'checkboxes',
	    '#title' => t('Display the button in these view modes:'),
	    '#options' => $locations,
	    '#default_value' => variable_get('weibo_sharebutton_node_location', array('full')),
	  );

	  $form['display']['weibo_sharebutton_weight'] = array(
	     '#type' => 'weight',
	     '#title' => t('Weight'),
	     '#delta' => 50,
	     '#default_value' => variable_get('weibo_sharebutton_weight', '-10'),
	     '#description' => t('Heavier items will sink. The default weight -10 will show the button at the top of the node content.'),
	  );

	  $available_sizes = array(
	    '3' => t('Small'),
	    '2' => t('Medium'),
	    '1' => t('Large'),
	  );
	  $available_icons = array(
	    '3' => t('Button'),
	    '0' => t('Icon'),
	  );
	  $default = array(
		'icontype' => '0',
	    'count' => 0,
	    'size' => 1,  // standard
	    'css' => 'margin: 0 1em 1em 1em;float:right',
	  );
	  $button_settings = variable_get('weibo_sharebutton_button_settings', $default);
	  $form['weibo_sharebutton_button_settings'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Button Settings'),
	    '#tree' => TRUE, // All the options in this fieldset will be grouped in 1 single variable.
	  );
	  $form['weibo_sharebutton_button_settings']['icontype'] = array(
	    '#type' => 'radios',
	    '#title' => t('Icon or Button Display?'),
	    '#options' => $available_icons,
	    '#default_value' => $button_settings['icontype'],
		  );
	  $form['weibo_sharebutton_button_settings']['count'] = array(
	    '#type' => 'radios',
	    '#title' => t('Include count?'),
	    '#options' => array(t('No'), t('Yes')),
	    '#default_value' => $button_settings['count'],
	  );
	  $form['weibo_sharebutton_button_settings']['size'] = array(
	    '#type' => 'radios',
	    '#title' => t('Size'),
	    '#options' => $available_sizes,
	    '#default_value' => $button_settings['size'],
	  );
	  $form['weibo_sharebutton_button_settings']['css'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Optional wrapper with CSS'),
	    '#maxlength' => 256,
	    '#default_value' => $button_settings['css'],
	    '#description' => t('To help with the layout and placement of the button, it will be rendered by default inside a wrapper: <br />	&lt;div class="wb_sharebutton-wrapper"&gt;	&lt;/div&gt;<br/>You can enter CSS rules to style this wrapper. By default <em>margin: 0 1em 1em 1em;float:right</em><br />To disable totally the wrapper, input the word <em>nowrapper</em>'),
	  );	
	  return system_settings_form($form);
}

/*
 * Trim and polish text input fields
*/
function weibo_sharebutton_admin_settings_validate($form, &$form_state) {
	  $form_state['values']['weibo_sharebutton_button_settings']['css'] = weibo_sharebutton_trim($form_state['values']['weibo_sharebutton_button_settings']['css'], ';');
	}

/**
 * Helper function to trim whitespace and make sure to remove
 * the last character if it is a delimiter.
 *
 * @param $list
 *   A string representing a list of items
 * @param $delimiter
 *   A string that contains a delimiter.
 * @return
 *   A whitespace-trimmed string
 *
*/
function weibo_sharebutton_trim($list, $delimiter) {
	$list = trim(check_plain($list));
	  if (!empty($list)) {
	    if (drupal_substr($list, -1) === $delimiter) {
	      $list = drupal_substr($list, 0, -1);
	    }
	  }
	return $list;
}
	
