using System;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using UnityEngine;
using System.Globalization;
using System.Threading;

using System.Runtime.InteropServices;

public class Controller : MonoBehaviour
{
    private static bool debug = true;
    public GameObject head;
    public GameObject user;
    public GameObject leftEye;
    public GameObject rightEye;
    public Camera camera;
    public GameObject plane;

    Vector3 eyeOrientVect;
    Vector3 cameraOrientVect;
    Vector3 righteye;
    Vector3 lefteye;

    private UnityClient unityClient;

    public Transform[] babyPlanes;

    const int NUM_GRIDS = 16;

    void Start () 
    {
        Debug.Log("*** Starting up Robot Head ***");
          
        unityClient = new UnityClient("head");
        if (!unityClient.ConnectToServer("127.0.0.1", 12345)) {
            Debug.Log("*** Can't connect to server ***");
        }

        string[] initialValues = new string[5];
        for (int i = 0; i < 5; i++) {
            initialValues[i] = unityClient.ReceiveMessage();
            unityClient.ReceiveMessage();
        }

        Debug.Log("*** message recieved, these are the initial values: ***");
        for (int i = 0; i < 5; i++) {
            Debug.Log(initialValues[i]);
        }

        // Setup environment variables (treating the camera as the center point)
        // Inputs effect the x coordinate of the game objects. y and z coordinates are standardized.

        // float camPos = float.Parse((string) initialValues[0]);  // camera position
        // float headDist = float.Parse((string) initialValues[1]); // how far head should be from camera
        // float targetDist = float.Parse((string)initialValues[2]); // distance from camera to target
        // string monitorSize = initialValues[3]; // appears as "hxw" where height is replaced with the actual height and w is replaced with the actual width
        // string resolution = initialValues[4]; // appears as "yxz". example input would be "1080x920"

        // ** place default values here **
        float camPos = 0.0f;
        float headDist = -1.0f;
        float targetDist = 1.0f;
        float result = 0.0f;  
        if (float.TryParse(initialValues[0], out result)){
            // use your valid result here
            Debug.Log("*** first ***");
            Debug.Log(result);
            camPos = result;
        }

        float result2 = 0.0f;  
        if (float.TryParse(initialValues[1], out result2)){
            // use your valid result here
            Debug.Log("*** second ***");
            Debug.Log(result2);
            headDist = result2;
        } 
        float result3 = 0.0f;
        if (float.TryParse(initialValues[2], out result3)){
            // use your valid result here
            Debug.Log("*** third ***");
            Debug.Log(result3);
            targetDist = result3;
        } 

        // float camPos = float.Parse("0.0");  // camera position
        // float headDist = float.Parse("5.0"); // how far head should be from camera
        // float targetDist = float.Parse("10.0"); // distance from camera to target
        string monitorSize = initialValues[3]; // appears as "hxw" where height is replaced with the actual height and w is replaced with the actual width
        string resolution = initialValues[4]; // appears as "yxz". example input would be "1080x920"

        head = Instantiate(head, new Vector3(-headDist, 0, 0), Quaternion.identity);
        leftEye = Instantiate(leftEye, new Vector3(0.13f + -headDist,-0.015f, -0.076f), Quaternion.identity);
        rightEye = Instantiate(rightEye, new Vector3(0.13f + -headDist, -0.015f, 0.076f), Quaternion.identity);
        leftEye.transform.parent = head.transform;
        rightEye.transform.parent = head.transform;

        camera = (Camera) Instantiate(camera, new Vector3(camPos,0,0), Quaternion.Euler(new Vector3(0, 270, 0)));
        // user = Instantiate(user, new Vector3(0.5f,0,0), Quaternion.Euler(new Vector3(0, 0, 0))); <- currently user does not serve much of a purpose, but saving here in case its needed
        plane = Instantiate(plane, new Vector3(targetDist,0,0), Quaternion.Euler(new Vector3(0, 0, 90)));

        // for cross looking
        eyeOrientVect = new Vector3(1, 0, 0);
        babyPlanes = new Transform[NUM_GRIDS];
        for (int i = 0; i < NUM_GRIDS; i++) {
            babyPlanes[i] = plane.transform.GetChild(i);
        }
    }

    void Update() {
        // Constantly listen for new messages for gaze
        //acceptAndModifyQuats();
    }

    // camera focal length is increased by same scale that robot head position is changed
     void updateCameraPosition(float x) {
        float oldX = camera.transform.position.x;
        float scale = x/oldX;
        camera.focalLength = camera.focalLength * scale;
        camera.transform.position = new Vector3(x, camera.transform.position.y, camera.transform.position.z);
    }

     void updateHeadPosition(float x, float y, float z) {
        head.transform.position = new Vector3(x, y, z);
    }

     void updateCameraFocalLength(float f) {
        // use f to focal length
    }

    // Method to make sure server code is functioning properly
    void acceptAndModifyQuats() {
        Quaternion[] rots = ConvertToQuats(unityClient.ReceiveMessage());
        if (rots != null) {
            Debug.Log(rots[0]);
            Debug.Log(rots[1]);
            rightEye.transform.rotation = rots[0];
            leftEye.transform.rotation = rots[1];
        } else {
            //Debug.Log("rots is null. Message received badly structured");
        }
    }

      /*
        Custom method to read in 6 float values from a string (usually a server message).
        This converts the string to a Quaternion array with Quaternion.Euler.
        The expected string format is: "1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0"" 
        where each comma-separated value (in order from left to right) is the W (scalar), X, Y, and Z rotation (first 3 are left eye, second 3 are right eye).
        If the processed string is not
        returns null if msg was invalid (doesn't contain all floats or not enough floats passed in)
        Otherwise, returns a Quaternion using Euler on the three expected float values
    */
    public static Quaternion[] ConvertToQuats(string msg)
    {
        if (debug) Debug.Log("Message to convert: " + msg);

        // Try-catch for if the values read in are not floats.
        try
        {
            msg =  Regex.Match(msg, @"[-0-9,.]+").Value;
            string[] rotValues = msg.Split(',');

            if (debug) Debug.Log("rotValues.Length: " + rotValues.Length);

            if (rotValues.Length != 8)
            {
                return null;
            }

            float w, x, y, z, w2, x2, y2, z2;

            if (!float.TryParse(rotValues[0], System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out w) ||
                !float.TryParse(rotValues[1], System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out x) ||
                !float.TryParse(rotValues[2], System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out y) ||
                !float.TryParse(rotValues[3], System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out z) ||             
                !float.TryParse(rotValues[4], System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out w2) ||
                !float.TryParse(rotValues[5], System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out x2) ||
                !float.TryParse(rotValues[6], System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out y2) ||
                !float.TryParse(rotValues[7], System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out z2)
                )
            {
                return null;
            }

            return new Quaternion[] { new Quaternion(w, x, y, z),new Quaternion(w2, x2, y2, z2) };
        }
        catch (Exception e)
        {
            Debug.Log(e);
            return null;
        }
    }
}