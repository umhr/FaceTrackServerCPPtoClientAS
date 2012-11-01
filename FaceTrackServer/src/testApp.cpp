#include "testApp.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
void testApp::setup(){
    ofSetWindowShape(320, 240);
    camera.setDeviceID(0);
    camera.initGrabber(320, 240);


    image.allocate(320, 240, OF_IMAGE_COLOR);
    //finder.setup("haarcascade_mcs_mouth.xml");
    finder.setup("haarcascade_frontalface_alt_tree.xml");
    msec = ofGetElapsedTimeMillis();

	netWorksetup();
}
void testApp::netWorksetup(){
	//we run at 60 fps!
	ofSetVerticalSync(true);

	//setup the server to listen on 11999
	TCP.setup(8087);
	//optionally set the delimiter to something else.  The delimter in the client and the server have to be the same, default being [/TCP]
	TCP.setMessageDelimiter("\n");
}


//--------------------------------------------------------------
void testApp::update(){
    camera.grabFrame();

    //  camera -> image
    unsigned char *cdata = camera.getPixels();
    unsigned char *idata = image.getPixels();
    for (int k = 0; k < 320*240*3; k++)
        idata[k] = cdata[k];
    image.update();
    //  face detection
    finder.findHaarObjects(image, 40, 40);

}

void testApp::netWorkupdate(string senndData){

	//for each client lets send them a message letting them know what port they are connected on
	for(int i = 0; i < TCP.getLastID(); i++){
		if( !TCP.isClientConnected(i) )continue;

		TCP.send(i, senndData );
	}
}
//--------------------------------------------------------------
void testApp::draw(){
    //  draw image
    ofSetColor(255, 255, 255);
    image.draw(0, 0);

    //  compute fps
    int msecNow = ofGetElapsedTimeMillis();
    float fps = 1000.0 / (msecNow - msec);
    msec = msecNow;

    //  draw markers
    ofSetColor(255, 0, 0);
    ofSetLineWidth(3);
    char buf[100];
    sprintf(buf, "%5.2f fps", fps);
    ofDrawBitmapString(buf, 20, 20);

	//img.draw(100, 100);
	ofNoFill();

	string senndData;
	senndData = "";

	for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(cur.x, cur.y, cur.width, cur.height);

		senndData += "{";
		senndData += "index:"+ofToString(i);
		senndData += ",x:"+ofToString(cur.x);
		senndData += ",y:"+ofToString(cur.y);
		senndData += ",width:"+ofToString(cur.width);
		senndData += ",height:"+ofToString(cur.height);
		senndData += "}";

		//netWorkupdate(cur.x, cur.y, cur.width, cur.height);
	}

	netWorkupdate(senndData);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
