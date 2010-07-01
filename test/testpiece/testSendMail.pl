#!/usr/bin/perl

###################################################

# send_mail.pl

# Send mail.

# Created by qiudi(Liyanling): 2010.4.2

# Last modified by qiudi(Liyanling): 2010.4.2

###################################################

use strict;

use warnings;

use Mail::Sender;

use Time::localtime;

my $logtime = sprintf("%d-%02d-%02d %02d:%02d:%02d",

        localtime(time())->year+1900,localtime(time())->mon+1,

        localtime(time())->mday,localtime(time())->hour,

        localtime(time())->min,localtime(time())->sec);


send_mail();


sub send_mail

{

    my $message = "以下是perl发送邮件测试。";

    my $space = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

    if ($message ne "")

    {

        $message ="您好！\n    $message\n\n\n"."

            $message .= $space."   Monitor center\n";

        $message .= $space."    Qiudi(Liyanling)\n";

        $message .= $space.$logtime;

        my $subject = "邮件测试";

        my $mailhost = 'smtp.gmail.com';

        my $mailfrom = 'djx_zh@sina.com';

        my $mailto = 'djx.zhenghua@gmail.com';

        my $ccaddr = 'david.dai@iccpcdev.com';

        print "Send mail ......\n";

        my $sender = new Mail::Sender{

            smtp => $mailhost,

                 from => $mailfrom,

        };

        If ($sender->MailMsg({

                    to => $mailto,

                    cc => $ccaddr,

                    subject => $subject,

                    msg => $message,

                    charset => 'gb2312'

                    }) < 0) {

            die "$Mail::Sender::Error\n";

        }

        print "Mail send OK.\n";

        $sender->Close;

    }

}
