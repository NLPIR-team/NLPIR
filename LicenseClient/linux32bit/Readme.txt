1.Set the license program with executive permission using the following command 将授权程序设置可执行权限；
	chmod +x license；
	
2.Using the following command to register your information according to the prompt [Attention: the organization should use given name].  注册的时候，执行:
   license -r [filename.user]
	The 3rd arguments is license file to be registered. Default is lingjoin.user.  第三个参数是授权文件，如果为空，则默认为lingjoin.user
	
3.After fill related information, execute the following command to activate your license file. 填报相关数据信息后，执行如下命令，
   license -a [filename.user]
 The 3rd arguments is license file to be activated. Default is lingjoin.user.  第三个参数是授权文件，如果为空，则默认为lingjoin.user
	
4.Input the given Serial Number to activate your license [The licensed computer must be connected with Internet]. If success, you can get NLPIR valid license, otherwise it will give the failure reason
 按照提示将客户经理提供的SN号输入，在线激活成功后【需要能连上我们的授权服务器】，即可获取商用授权。
