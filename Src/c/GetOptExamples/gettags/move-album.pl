#!/usr/bin/perl -w

# A script that uses gettags to copy a bunch of music files to a new directory
# whose name is given by ${target_dir}/${album}/${title}/${extension}
# Where $target_dir is the first argument to the script, $title and
# $album are taken from the music file, and $extension is the original file
# extension
#
# Example:
#
# move_album.pl /media/my_albums /tmp/my_cd_rips/*.mp3

use strict;

die "Usage: move_album.pl {directory} {files...}" if (scalar(@ARGV) < 1);

my $target_dir = $ARGV[0];
print "target=", $target_dir, "\n";

system ("mkdir -p \"$target_dir\"");

for (my $i = 1; $i < scalar(@ARGV); $i++)
  {
  my $file = $ARGV[$i];
  my $album = `gettags -c album "$file"`;
  chomp ($album);
  if ($album)
    {
    my $title = `gettags -c title "$file"`;
    chomp ($title);
    if ($title)
      {
      my $ext = ($file =~ m/([^.]+)$/)[0];
      my $album_dir = "${target_dir}/${album}";
      my $target_file = "${album_dir}/${title}.${ext}";
      system ("mkdir -p \"${album_dir}\"");
      print "Copying file ", $file, "\n to ", $target_file, "\n";
      my $cmd = "cp \"$file\" \"$target_file\""; 
      system ($cmd);
      }
    }
  else
    {
    print "No album tag in '", $file, "\n";
    }
  }

