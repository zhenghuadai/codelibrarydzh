#!/usr/bin/perl 
use strict;

open LOG, ">/tmp/cpln.log" or die "can not open ";
main(@ARGV);
close(LOG);

sub linkTo{
	my ($srcfn, $dstfn) = @_;
	if( -e $dstfn){
	}else {
		`ln -s $srcfn $dstfn`;
	}
}

sub linkToFolders
{
	my ($dir, $dstDir)=@_;
	my $next;
	opendir dir, $dir or die "Cannot open $dir : $!";
	if ( -d $dstDir ){
	} else {
		`mkdir $dstDir`;
	}
	foreach $next (readdir dir) {
		next if "$next" eq "." or "$next" eq ".." or "$next" eq ".svn";
		if ( -f "$dir/$next" ){
			linkTo("$dir/$next", "$dstDir/$next");
		}
		elsif ( -d "$dir/$next" ) {
			&linkToFolders("$dir/$next", "$dstDir/$next");
		}
	}
	closedir (dir);
	return;
}

sub main(){
	my $pwd = `pwd`;
	my $numargs = @ARGV;
	if( $numargs ==0 ) {
		printf "cpln srcDir dstDir\n";
		exit;
	}
	if ( -f $ARGV[0]){
		`ln -s $ARGV[0] $ARGV[1]`;
	} else {
		my $srcDir = $ARGV[0];
		if( $srcDir !~ "^\/") {
			chomp($pwd);
			$srcDir = "$pwd/$srcDir";
		}
		
		linkToFolders($srcDir,$ARGV[1]);
	}
}
