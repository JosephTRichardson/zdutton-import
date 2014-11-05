<?php

$input_dir = '/sites/all/modules/zdutton_import/zdutton/data';
#$output_dir = 'C:\Users\Joseph\Documents\zdutton\drupal';

$slugs = array();

function zdutton_import_do_import() {
	// chdir($input_dir); #  die "Couldn't chdir to $input_dir: $!";
	$listing = zdutton_import_get_listing();
	drupal_set_message('status', 'Got file listing.');
	//zdutton_import_catalog($listing);
	//zdutton_import_convert($listing);
}

function zdutton_import_get_listing() {
	$listing = array();
	$dh = opendir($input_dir); # or die "Couldn't opendir $input_dir: $!";
	while (false !== ($entry = readdir($dh))) {
		if (! is_dir($entry) && preg_match('/\.html$/', $entry)) {
			$listing[] = $entry;
		}
	}
	closedir($dh);
	return $listing;
}

function zdutton_import_catalog($listing) {
	global $slugs;
	foreach ($listing as $file) {
		$data = zdutton_import_read_zfile($file);
		$title = $data['TITLE'];
		if (! $title) {
			drupal_set_message('error', "$file has no TITLE attribute");
			return;
		}
		$slug = zdutton_import_to_slug($title);
		$slugs[$file] = $slug;
		#print "$htmlfile => $slug\n";
	}
}

function zdutton_import_convert($listing) {
	foreach ($listing as $file) {
		#print "Converting $htmlfile\n";
		$data = zdutton_import_read_zfile($htmlfile);
		#print "Got ", length($htmlcontent), " bytes of HTML content.\n";
		$content = $data['content'];
		$content = preg_replace_callback('/(<a[^>]* href=")([^"]+)("[^>]*>.*?<\/a>)/',
			'zdutton_import_rewrite_link', $content);
		$slug = $slugs[$htmlfile];
		zdutton_import_create_node($slug, $content);
		drupal_set_message('status', "Processed $file.");
		print "<div>Processed $file.</div>\n";
	}
}

function zdutton_import_rewrite_link($matches) {
	$prematch = $matches[1];
	$href = $matches[2];
	$postmatch = $matches[3];
	
	$url_components = parse_url($href);
    # scheme, host, port, user, pass, path, query, fragment

	if (! preg_match('/^\w+\.html$/', $url_components['path'])) {
		drupal_set_message('warning', "Unrecognized URI: $uri");
		return $matches[0];
	}
	// print "$uri => ";
	$file = $url_components['path'];
	// print "$file => ";
	if (! array_key_exists($file, $htmlfiles)) {
		drupal_set_message('warning', "Unknown file: $file");
	}
	$slug = $slugs[$file];
	#print "$slug => ";
	$new_href = $slug;
	if ($url_components['fragment']) {
		$new_href .= '#' . $url_components['fragment'];
	}
	#print "$new_href\n";
	
	return $prematch . $new_href . $postmatch;
}

function zdutton_import_to_slug($title) {
	$title = strtolower($title);
	$title = str_replace(' ', '-', $title);
	$title = preg_replace('/[^\w-]/', '', $title); 
	return $title;
}

function zdutton_import_read_zfile($htmlfile) {
	#my ($content, $data);
	#fopen ($htmlfile, "r"); # or die "Couldn't open $htmlfile: $!";
	#while (<$fh>) {
	#	last if m/__DATA__/;
	#	push @data, $_;
	#}
	$lines = file($htmlfile);
		
	# Data include TITLE, UP_TITLE, UP_HREF, etc.
	# This will help us establish parental/hierarchical relationships between the pages
	$data = array();
	while ($line = array_shift($lines)) {
		rtrim($line);
		if (preg_match('/^(\w+?)=(.*)$/', $line, $matches)) {
			$field = $matches[1];
			$value = $matches[2];
			$data[$field] = $value;		
		} else if ($line == "__DATA__") {
			break;
		}
	}
	$content = implode($lines);
	$data['content'] = $content;
	return $data;
}