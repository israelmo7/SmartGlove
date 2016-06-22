from socket import *

def main():
#connection:
	address = ("127.0.0.1", 80)
    
	my_soc = socket()
    
	my_soc.connect(address)
		
#begin dynamic program:
	
	while (True):
		line = raw_input("Enter line:")
		if line == "e" or len(line) != 15:
			break
		
		print "finger[0]: " + line[0:2] + "/n"
		print "finger[1]: " + line[2:4] + "/n"
		print "finger[2]: " + line[4:6] + "/n"
		print "X Axis: " + line[6:9] + "/n"
		print "Y Axis: " + line[9:12] + "/n"
		print "Z Axis: " + line[12:15] + "/n"
		
		my_soc.send(line)

#close:
	my_soc.close()
	

#define:
if __name__ == "__main__":
	main()