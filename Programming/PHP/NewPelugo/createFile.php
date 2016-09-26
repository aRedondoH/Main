<?php 
//$filename = 'http://www.pelugo.es/php_pelugo/maps/test.txt';
$filename = 'test.txt';
$Content = "Add this to the file\r\n";
 
echo "open";
$handle = fopen($_SERVER['DOCUMENT_ROOT']. '/php_pelugo/maps/' .$filename , 'x+');
echo " write";
fwrite($handle, $Content);
echo " close";
fclose($handle);
 

if($handle = fopen($filename, 'a')){
if(is_writable($filename)){
if(fwrite($handle, $content) === FALSE){
echo "Cannot write to file $filename";
exit;
}
echo "The file $filename was created and written successfully!";
fclose($handle);
}
else{
echo "The file $filename, could not written to!";
exit;
}
}
else{
echo "The file $filename, could not be created!";
exit;

}
?>
