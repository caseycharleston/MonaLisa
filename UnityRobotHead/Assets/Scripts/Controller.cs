using System;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using UnityEngine;

using System.Runtime.InteropServices;
/*

Project Design Strategy:

Monitor -> User -> Targets

Robot head will be the location of the monitor. the User object will be where the user sits relative
to the monitor. Target object will be the grid of lookable targets

*/
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
        // initalize head

        /* Settings for Production */
        // float headDist = 1.0f; // distance from camera
        // head = Instantiate(head, new Vector3(0, 0, -headDist), Quaternion.identity);
        // leftEye = Instantiate(leftEye, new Vector3(0.13f,-0.015f,-headDist + -0.076f), Quaternion.identity);
        // rightEye = Instantiate(rightEye, new Vector3(0.13f,-0.015f,-headDist + 0.076f), Quaternion.identity);
        // leftEye.transform.parent = head.transform;
        // rightEye.transform.parent = head.transform;
        // head.transform.rotation = Quaternion.Euler(new Vector3(0, -90, 0));

        // camera = (Camera) Instantiate(camera, new Vector3(0,0,0), Quaternion.Euler(new Vector3(0 ,-180, 0)));
        // user = Instantiate(user, new Vector3(0,0,0.5f), Quaternion.Euler(new Vector3(0, -180, 0)));
        // plane = Instantiate(plane, new Vector3(0,0,1), Quaternion.Euler(new Vector3(0, -90, 90)));

        /* Settings for Demo. For some reason, lookAt does not work if head is normalized on Z axis */
        float headDist = 1.0f; // distance from camera
        head = Instantiate(head, new Vector3(-headDist, 0, 0), Quaternion.identity);
        leftEye = Instantiate(leftEye, new Vector3(0.13f + -headDist,-0.015f, -0.076f), Quaternion.identity);
        rightEye = Instantiate(rightEye, new Vector3(0.13f + -headDist, -0.015f, 0.076f), Quaternion.identity);
        leftEye.transform.parent = head.transform;
        rightEye.transform.parent = head.transform;

        camera = (Camera) Instantiate(camera, new Vector3(0,0,0), Quaternion.Euler(new Vector3(0, 270, 0)));
        user = Instantiate(user, new Vector3(0.5f,0,0), Quaternion.Euler(new Vector3(0, 0, 0)));
        plane = Instantiate(plane, new Vector3(1,0,0), Quaternion.Euler(new Vector3(0, 0, 90)));

        // for cross looking
        eyeOrientVect = new Vector3(1, 0, 0);
        babyPlanes = new Transform[NUM_GRIDS];
        for (int i = 0; i < NUM_GRIDS; i++) {
            babyPlanes[i] = plane.transform.GetChild(i);
        }
        // Server Client
        unityClient = new UnityClient("head");
        unityClient.ConnectToServer("127.0.0.1", 12345);
    }

    void Update() {
        // lookAt(babyPlanes[5].position);
        // Debug.Log(leftEye.transform.rotation);
        // Debug.Log(rightEye.transform.rotation);
        acceptAndModifyQuats();
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
    
    // Vector3: 3 floats, not necessarily pos or rot
    // position: gotten from Transform.position
    // 
    public void lookAt(Vector3 target) {
        // get location, rotation
        Vector3 rEyePos = rightEye.transform.position;
        Vector3 lEyePos = leftEye.transform.position;
        Vector3 lEyeVect = target - lEyePos;
        Vector3 rEyeVect = target - rEyePos;
        lEyeVect = Vector3.Normalize(lEyeVect);
        rEyeVect = Vector3.Normalize(rEyeVect);
        // draw laser eyes (superman)
        Debug.DrawRay(rEyePos, rEyeVect * 10000000, Color.red, 100000f);
        Debug.DrawRay(lEyePos, lEyeVect * 10000000, Color.red, 100000f);
        Vector3 lcross = Vector3.Cross(eyeOrientVect, lEyeVect);
        Vector3 rcross = Vector3.Cross(eyeOrientVect, rEyeVect);
        float langle = Vector3.Angle(lEyeVect, eyeOrientVect);
        float rangle = Vector3.Angle(rEyeVect, eyeOrientVect);
        lcross = Vector3.Normalize(lcross);
        rcross = Vector3.Normalize(rcross);
        // this rotation should be done in C++ file epic
        // we need to rigidly transform the eye by M_eyeLook (to create M_eyePose)
        // the eye (left eye for example) is currently at M_head * M_eye_l
        rightEye.transform.rotation = Quaternion.AngleAxis(rangle, rcross);
        leftEye.transform.rotation = Quaternion.AngleAxis(langle, lcross);
    }

    void TestServer() {
        // test code
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
            Debug.Log("rots is null. Message received badly structured");
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