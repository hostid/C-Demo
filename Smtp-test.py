'''
@FileName: 
@Descripttion: 
@Author: jiangfeng.zhang(jiangfeng.zhang@aliyun.com)
@LastEditTime: 2019-11-01 11:29:33
'''
import smtplib
from email.mime.text import MIMEText
email_host = 'smtp.126.com'     #邮箱地址
email_user = 'retries@126.com'  # 发送者账号
email_pwd = 'Aa408441'  # 发送者的密码，注意这里的密码指的是smtp服务的授权码，并不是你的登录密码
maillist ='jiangfeng.zhang@aliyun.com'
#收件人邮箱，多个账号的话，用逗号隔开
me = email_user
msg = MIMEText('这是个python测试邮件，不用回复。')    # 邮件内容
msg['Subject'] = 'python测试'    # 邮件主题
msg['From'] = me    # 发送者账号
msg['To'] = maillist    # 接收者账号列表
smtp = smtplib.SMTP(email_host,port=25) # 连接邮箱，传入邮箱地址，和端口号，smtp的端口号是25
smtp.login(email_user, email_pwd)   # 发送者的邮箱账号，密码
smtp.sendmail(me, maillist, msg.as_string())
# 参数分别是发送者，接收者，第三个是把上面的发送邮件的内容变成字符串
smtp.quit() # 发送完毕后退出smtp
print ('email send success.')