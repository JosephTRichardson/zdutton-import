# ZDutton Import
A Drupal 7 module to import and update my old genealogy website.

## Overview

This project is a Drupal 7 module designed to import my old genealogy
website, the [Zachariah Dutton Genealogy Web](http://wwww.zdutton.org)
or ZDutton.org, into a Drupal environment. The old ZDutton.org exists
in a hundred or so "raw HTML" files — that is, HTML files stripped of
their headers and footers, to which I formerly applied a basic, offline
Perl preprocessor to give more-or-less dynamic content.

The goals of this project were simple at first: read in the raw HTML
files (each describing a family group), transform their internal links
to appropriate new URLs (e.g. "wdutton.html" to "william-dutton-and-mary-hogan"),
and re-create them as Drupal nodes. When I began, I knew next-to-nothing
about the Drupal API; as I've learned more and come to better understand
the API and what it is capable of, my goals have expanded — such that
the more I know I *can* do, the more I *want* to do. Now, with an end
only vaguely in sight, the project has become as much about learning how
to do things in Drupal as it is about the utilitarian function of
updating my website.

Among the things this module now accomplishes:

1. Read in the raw HTML files and transform their internal links.
2. Create a new Drupal content type, a "family group" page, to accept
   the family group content.
3. Create a new text format, "raw HTML," to bypass the
   automatic-line-ending filter and accept the raw ZDutton content
   without having line breaks inserted.
4. Create a new taxonomy vocabulary for "family groups," and create a
   hierarchical taxonomy based on the family tree (the structure of
   which was already present in the metadata of the old "raw HTML"
   files); create appropriate fields and references to accommodate
   this vocabulary.
    * Each family group page is assigned a taxonomy term equal to its
      title (the name of the family, e.g. "William Dutton and Mary Hogan).
      Nodes containing related content, e.g. photo galleries, are given
      the same taxonomy term as the family group to which they relate —
      i.e. every page having content to do with William Dutton and Mary
      Hogan will have the "William Dutton and Mary Hogan" taxonomy term
      in a term reference field.
5. Based on this family group taxonomy, dynamically generate Drupal
   breadcrumbs showing the path back to the top of the tree.

I don't suppose anybody else will want to import or re-create the
Zachariah Dutton Genealogy Web, but it is my hope that this code might
be beneficial to somebody else learning how to do things in Drupal.

## History

Years ago, in 1999, I was hot out of high school and excited about more
things than I could keep straight. Among those things were genealogy
and the Internet, and like most kids those days, I was proud to have
made a few primitive websites. I had gathered an eager following of
cousins from all over the U.S. for my genealogy mailing list, focused
on the research of my ancestor Zachariah Dutton. And I decided a
website presenting our research would serve the group well, both to
inform and to attract new cousins.

It wasn't bad, for 1999. I was an avid early adopter of Web standards,
followed the W3C's recommendations religiously, and turned my nose at
all the lamers who used &lt;FONT&gt; tags and other presentational elements
in their HTML. I hand-coded a site full of valid HTML 4.01 and CSS1 that
communicated all the data I needed to communicate, and I'm still proud
of that.

Though on the surface bare and spartan, behind the scenes, I was doing
some cool things. I realized the necessity of tracking my updates to
document the changes I made and why, so I maintained the whole thing in
a CVS repository. It seemed unprofessional and a hassle to have to
manually update my "Last changed" footers every time I updated a page,
so I conceived of a Perl preprocessor that would "bake" my "raw" HTML
files offline before every upload, adding appropriate and more-or-less
dynamic headers and footers to my bare data, with navigational and
informational elements, based on private headers for each page. PHP was
still a New Thing then, and I never realized that I was reinventing a wheel.

Now it's 2014, fifteen years after all of that. I largely stopped
updating the website, called the "Zachariah Dutton Genealogy Web,"
years ago, and gradually things broke down. The site is still there,
but is not much to look at, and as much as I still love it, it is
something of an embarrassment to have my name attached to while I'm
looking for work and touting myself as a Web developer. So I decided
it was time to act. Rather than do the sensible thing and simply plug
it all into a basic PHP framework and style it, I decided to
reinvent the wheel *again*, and roll it up the steep learning curve
of Drupal. This project documents my efforts.

## License

This project and code, like [Drupal](https://www.drupal.org/licensing/faq)
itself, are released under the GNU
[General Public License, version 2 or later](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
This means that you are free to copy, modify, and redistribute it, or
incorporate all or part into your own project, provided that you keep
intact the attribution to me and this license information, and that in
the case of any derivative works, you likewise make the source code
free and available under these same terms.

Copyright 2014, [Joseph T. Richardson](mailto:joseph.t.richardson@gmail.com) (LonelyPilgrim @ GitHub).
