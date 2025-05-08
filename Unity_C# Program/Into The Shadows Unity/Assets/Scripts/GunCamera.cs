using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GunCamera : MonoBehaviour
{
    //camera movement variables
    public float sensitivity_vert = 4f;
    public float sensitivity_horiz = 4f;
    float xRotation = 0f;
    float yRotation = 0f;

    // reference to the camera audio listener
    [SerializeField] private AudioListener audioListener;
    // reference to the camera
    [SerializeField] private Camera playerCamera;

    public float CameraRangeUp = -50f;
    public float CameraRangeDown = 9f;

    void Update()
    {
        // Camera movement
        float mouseX = Input.GetAxis("Mouse X") * sensitivity_horiz;
        float mouseY = Input.GetAxis("Mouse Y") * sensitivity_vert;

        yRotation += mouseX;
        xRotation -= mouseY; //up and down cursor movement, rotation of the cam along x axis
        xRotation = Mathf.Clamp(xRotation, CameraRangeUp, CameraRangeDown);

        //transform.rotation = Quaternion.Euler(0f, yRotation, 0f);
        playerCamera.transform.localRotation = Quaternion.Euler(xRotation, 0f, 0f);
    }
}
