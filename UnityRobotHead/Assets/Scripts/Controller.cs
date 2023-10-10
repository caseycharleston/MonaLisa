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

private const int NUM_GRIDS = 16;

    void Start () 
    {
        // initalize head
        head = Instantiate(head, new Vector3(0,0,0), Quaternion.identity);
        leftEye = Instantiate(leftEye, new Vector3(7,-0.65f,-3.8f), Quaternion.identity);
        rightEye = Instantiate(rightEye, new Vector3(7,-0.65f,3.8f), Quaternion.identity);
        camera = (Camera) Instantiate(camera, new Vector3(50,0,0), Quaternion.Euler(new Vector3(0, -90, 0)));
        user = Instantiate(user, new Vector3(60,0,0), Quaternion.Euler(new Vector3(0, -90, 0)));
        plane = Instantiate(plane, new Vector3(100,0,0), Quaternion.Euler(new Vector3(0, 0, 90)));

        // for cross looking
        eyeOrientVect = new Vector3(1, 0, 0);
        babyPlanes = new Transform[NUM_GRIDS];
        for (int i = 0; i < NUM_GRIDS; i++) {
            babyPlanes[i] = plane.transform.GetChild(i);
        }
    }

    void Update()
    {
        Debug.Log(camera);
        lookAt(babyPlanes[0].position);
    }

    private void updateHeadPosition(float x, float y, float z) {
        head.transform.position = new Vector3(x, y, z);
    }

    private void rotateLeftEye(Quaternion rotation) {
        leftEye.transform.rotation = rotation;
    }

    private void rotateRightEye(Quaternion rotation) {
        rightEye.transform.rotation = rotation;
    }

    private void updateCameraFocalLength(float f) {
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
        Debug.Log("lEyeVect " + lEyeVect);
        Debug.Log("rEyeVect " + rEyeVect);
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
        rightEye.transform.rotation = Quaternion.AngleAxis(rangle, rcross);
        leftEye.transform.rotation = Quaternion.AngleAxis(langle, lcross);
    }
}