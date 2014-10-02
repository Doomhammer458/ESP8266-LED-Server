# -*- coding: utf-8 -*-
import tornado.ioloop
import tornado.web
import tornado
import os
import random
import socket
def sendData(data):
    TCP_IP = '192.168.1.XX' #ip address of the esp8266
    TCP_PORT = 8266
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((TCP_IP, TCP_PORT))
    s.send(data)
    s.close()

    



class BaseHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("static/index.html")
    def post(self):
        try:
        
            color = self.get_argument("color")
            print color
            red = int(color[1:3],16)
            green = int(color[3:5],16)
            blue = int(color[5:],16)
            if any([blue>255,green>255,red>255]) or any([blue<0,green<0,red<0]):
                raise Exception
            sendString = "LED,"
            sendString+=str(red)
            sendString+=","
            sendString+=str(green)
            sendString+=","
            sendString+=str(blue)
            print sendString
            sendData(sendString)
            self.write("OK")

        except:
            self.write("Failed")

STATIC_PATH= os.path.join(os.path.dirname(__file__),r"static/")
application = tornado.web.Application([

	(r"/", BaseHandler),


],static_path=STATIC_PATH,login_url=r"/login/", debug=True,
 cookie_secret="35wfa35tgtres5wf5tyhxbt4"+str(random.randint(0,1000000)))

if __name__ == "__main__":

    
    application.listen(80)
    tornado.ioloop.IOLoop.instance().start()
    




