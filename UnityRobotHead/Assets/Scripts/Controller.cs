using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*

Project Design Strategy:

Monitor -> User -> Targets

Robot head will be the location of the monitor. the User object will be where the user sits relative
to the monitor. Target object will be the grid of lookable targets

*/
public class Controller : MonoBehaviour
{
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

public Transform[] babyPlanes; // TODO: store all positions of mini planes in here

 const int NUM_GRIDS = 16;

    void Start () 
    {
        // initalize head
        float headDist = 1.0f; // distance from camera
        head = Instantiate(head, new Vector3(0  ,0,-headDist), Quaternion.identity);
        leftEye = Instantiate(leftEye, new Vector3(0.13f,-0.015f,-headDist + -0.076f), Quaternion.identity);
        rightEye = Instantiate(rightEye, new Vector3(0.13f,-0.015f,-headDist + 0.076f), Quaternion.identity);
        leftEye.transform.parent = head.transform;
        rightEye.transform.parent = head.transform;
        head.transform.rotation = Quaternion.Euler(new Vector3(0, -90, 0));

        camera = (Camera) Instantiate(camera, new Vector3(0,0,0), Quaternion.Euler(new Vector3(0 ,-180, 0)));
        user = Instantiate(user, new Vector3(0,0,0.5f), Quaternion.Euler(new Vector3(0, -180, 0)));
        plane = Instantiate(plane, new Vector3(0,0,1), Quaternion.Euler(new Vector3(0, 90, 90)));

        // for cross looking
        eyeOrientVect = new Vector3(0, 0, 1);
        babyPlanes = new Transform[NUM_GRIDS];
        for (int i = 0; i < NUM_GRIDS; i++) {
            babyPlanes[i] = plane.transform.GetChild(i);
        }
    }

    void Update() {
        // lookAt(babyPlanes[0].position);      
    }

    // camera focal length is increased by same scale that robot head position is chan
     void updateCameraPosition(float x) {
        float oldX = camera.transform.position.x;
        float scale = x/oldX;
        camera.focalLength = camera.focalLength * scale;
        camera.transform.position = new Vector3(x, camera.transform.position.y, camera.transform.position.z);
    }

     void updateHeadPosition(float x, float y, float z) {
        head.transform.position = new Vector3(x, y, z);
    }

     void rotateLeftEye(Quaternion rotation) {
        leftEye.transform.rotation = rotation;
    }

     void rotateRightEye(Quaternion rotation) {
        rightEye.transform.rotation = rotation;
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
}