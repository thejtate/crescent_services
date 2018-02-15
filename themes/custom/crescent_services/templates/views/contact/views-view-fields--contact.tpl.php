<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */

$nid = (isset($fields['nid']->raw)) ? $fields['nid']->raw : NULL;

if (empty($nid)) {
  return;
}
?>

<div class="item-wrapper" id="city-<?php print $nid; ?>">
  <div class="col map-icon"></div>
  <div class="col">
    <div class="col-title">
      <?php print $fields['field_location_city']->content; ?>
      , <?php print $fields['field_location_state']->content; ?>
    </div>

    <?php if (isset($fields['field_location_address']->content)): ?>
      <div class="col-address">
        <?php print $fields['field_location_address']->content; ?>
      </div>
    <?php endif; ?>

    <?php if (isset($fields['field_location_phone']->content)): ?>
      <div class="col-phone">
        <?php print $fields['field_location_phone']->content; ?>
      </div>
    <?php endif; ?>

    <?php if (isset($fields['field_location_key_contacts']->content)): ?>
      <div class="col">
        <div class="col-title"><?php print t("Key Contacts") ?></div>
        <?php print $fields['field_location_key_contacts']->content; ?>
      </div>
    <?php endif; ?>

  </div>
</div>