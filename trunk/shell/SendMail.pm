#!/usr/bin/perl -w
#*****************************************************************************#
#  Function Name:
#       SendMail($$\@$$\@)
#  Description:
#       Use Net::SMTP and MIME::Lite to send Email with attachment.
#  Argument:
#       1: The Sender.
#       2: The recipient Email array.
#       3: The Subject of the Email.
#       4: The Content of the Email.
#       5: The attachments array of the Email.
#       6: The Passwd of sending Email.
#       7: The smtp host.
#       8: The usename on smtp host. 
#  Return:
#       None
#  Example:
#       my $mailFrom       = 'pubmail001@sina.cn';
#       my $password       = 'test123';
#       my $mailHost       = 'smtp.sina.com';
#       my $mailUser       = 'pubmail001@sina.cn';
#       my @mailTo         = ('@gmail.com','@sina.com');
#       my $mailSubject    = "Test Perl SendMail";
#       my $mailContent    = "The attachment is the $mailSubject!\n";
#       my @mailAttachment = ('testPerlMail2');    
#       SendMail($mailFrom,  \@mailTo, $mailSubject, $mailContent, \@mailAttachment, $password, $mailHost, $mailUser);
#*****************************************************************************#
package SendMail;
require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(SendMail
                                       );
use Net::SMTP;
use MIME::Lite;
sub SendMail # ($$\@$$\@)
{
    my ($From, $ToRef, $Subject, $Content, $AttachmentRef, $Passwd, $Host, $User)=@_;
    my @To = @$ToRef;   
    my @attachment = @$AttachmentRef;  

    my $helloPara = $Host;

    if( $Host eq ""){
        ($User, $Host) = split("/\@/", $From);
        $Host="smtp.".$Host;
    }

    ##################################################################################
    #                 Create smtp and ahth                                           #
    ##################################################################################
    my $smtp = Net::SMTP->new($Host, Hello => $helloPara, Timeout => 120, Debug => 1)
    ||die 'Cannot connect to server \'$Host\'';

    $smtp->auth($User,$Passwd)||die "Auth Error!\n";
    
    ##################################################################################
    #                 Create MIME  multipart message:                                #
    ##################################################################################
    my $msg = MIME::Lite->new(
        From    => $From,
        To      => join(',',@To),
        Subject => $Subject,
        Type    =>'multipart/mixed',
    )or print "Error creating MIME body: $!\n";

    # Add parts:
    $msg->attach(Type     =>'TEXT',
        Data    => $Content,
    );
    foreach my $attachment (@attachment)
    {
        $msg->attach(
            Type     => 'AUTO',      # the attachment mime type
            Path     => $attachment, # local address of the attachment
        )or print "Error attaching test file: $!\n";
        print "$attachment";
    }

    my $str = $msg->as_string() or print "Convert the message as a string: $!\n";

    ##################################################################################
    #                Send Mail                                                       #
    ##################################################################################
    $smtp->mail($From);
    $smtp->recipient(@To);
    $smtp->data();
    $smtp->datasend("$str");
    $smtp->dataend();

    ##################################################################################
    #                End Mail                                                        #
    ##################################################################################
    $smtp->quit;
    return;
}

