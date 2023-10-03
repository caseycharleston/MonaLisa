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
    public Transform head;
    public Transform user;
    public Transform target;
    //public Transform camera; 

    Vector3 eyeOrientVect;
    Vector3 cameraOrientVect;
    Vector3 righteye;
    Vector3 lefteye;

public GameObject gridPiece;
public Transform gridPieceTF;

public GameObject[] babyPlanes;

private const int NUM_GRIDS = 16;

    void Start () 
    {
        //babyPlanes = new GameObject[NUM_GRIDS];
        // for (int i = 0; i < NUM_GRIDS; i++) {
        //     string curPlane = "babyPlane" + (i + 1);
        //     babyPlanes[i] = GameObject.FindGameObjectsWithTag("babyPlane1")[0];
        // }
    }

    void Update()
    {
        Debug.Log("in updateee");
    }

    private void updateHeadPosition(float x, float y, float z) {
        GameObject face = GameObject.FindGameObjectsWithTag("MakiHead")[0];
        face.transform.position = new Vector3(x, y, z);
    }

    private void rotateLeftEye(Quaternion rotation) {
        GameObject leftEye = GameObject.FindGameObjectsWithTag("LeftEye")[0];
        leftEye.transform.rotation = rotation;
    }

    private void rotateRightEye(Quaternion rotation) {
        GameObject rightEye = GameObject.FindGameObjectsWithTag("RightEye")[0];
        rightEye.transform.rotation = rotation;
    }

    private void updateCameraFocalLength(float f) {
        Camera cam = Camera.main;
        cam.focalLength = f;
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