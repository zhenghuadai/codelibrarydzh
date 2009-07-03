#!/usr/bin/perl 
use strict;

main(@ARGV);
close(LOG);

sub doFile{
	my ($fn) = @_;
	open SRC, "<$fn" or die "can not open $fn" ; 
	while(my $line = <SRC> ){
		if( $line =~ "class ([a-zA-Z]+) : public ([a-zA-Z]+)"){
			printf "$1 -> $2;\n";
		}
	}
	close (SRC);
}

sub doFolders
{
	my ($dir)=@_;
	my $next;
	opendir dir, $dir or die "Cannot open $dir : $!";
	foreach $next (readdir dir) {
		next if "$next" eq "." or "$next" eq ".." or "$next" eq ".svn";
		if (( -f "$dir/$next" ) and ( $next =~ "$\.h")){
			doFile("$dir/$next");
		}
		elsif ( -d "$dir/$next" ) {
			&doFolders("$dir/$next");
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
	} else {
		my $srcDir = $ARGV[0];
		if( $srcDir !~ "^\/") {
			chomp($pwd);
			$srcDir = "$pwd/$srcDir";
		}
		
		doFolders($srcDir);
	}
}
