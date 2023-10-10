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

    public GameObject[] babyPlanes; // TODO: store all positions of mini planes in here

private const int NUM_GRIDS = 16;

    void Start () 
    {
        head = Instantiate(head, new Vector3(0,0,0), Quaternion.identity);
        leftEye = Instantiate(leftEye, new Vector3(7,-0.65f,-3.8f), Quaternion.identity);
        rightEye = Instantiate(rightEye, new Vector3(7,-0.65f,3.8f), Quaternion.identity);
        camera = (Camera) Instantiate(camera, new Vector3(50,0,0), Quaternion.Euler(new Vector3(0, -90, 0)));
        //Instantiate(user, new Vector3(60,0,0), Quaternion.Euler(new Vector3(0, -90, 0)));
        plane = Instantiate(plane, new Vector3(100,0,0), Quaternion.Euler(new Vector3(0, 0, 90)));
        // Debug.Log("before change: ");
        // Debug.Log(camera.transform.position);
        // Debug.Log("focal length: ");
        // Debug.Log(camera.focalLength);
    }

    void Update()
    {
        updateCameraPosition(500);
        Debug.Log("after change: ");
        Debug.Log(camera.transform.position);
        Debug.Log(camera.focalLength);
    }

    // camera focal length is increased by same scale that camera position is changed (if camera pos is only changed via x vector)
    private void updateCameraPosition(float x) {
        float oldX = camera.transform.position.x;
        float scale = x/oldX;
        camera.focalLength = camera.focalLength * scale;
        camera.transform.position = new Vector3(x, camera.transform.position.y, camera.transform.position.z);
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
    	GameObject reye = GameObject.FindGameObjectsWithTag("rightEye")[0];
        GameObject leye = GameObject.FindGameObjectsWithTag("leftEye")[0];
        // get location, rotation
        righteye = reye.transform.position;
        lefteye = leye.transform.position;
        Vector3 lEyeVect = target - lefteye;
        Vector3 rEyeVect = target - righteye;
        lEyeVect = Vector3.Normalize(lEyeVect);
        rEyeVect = Vector3.Normalize(rEyeVect);
        // draw laser eyes (superman)
        Debug.DrawRay(righteye, rEyeVect * 1000000, Color.red, 100000f);
        Debug.DrawRay(lefteye, lEyeVect * 1000000, Color.red, 100000f);
        Vector3 lcross = Vector3.Cross(eyeOrientVect, lEyeVect);
        Vector3 rcross = Vector3.Cross(eyeOrientVect, rEyeVect);
        float langle = Vector3.Angle(lEyeVect, eyeOrientVect);
        float rangle = Vector3.Angle(rEyeVect, eyeOrientVect);
        lcross = Vector3.Normalize(lcross);
        rcross = Vector3.Normalize(rcross);
        reye.transform.rotation = Quaternion.AngleAxis(rangle, rcross);
        leye.transform.rotation = Quaternion.AngleAxis(langle, lcross);
    }
}