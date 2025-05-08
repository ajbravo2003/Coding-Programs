using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCameraCollision : MonoBehaviour
{
    public Transform player;           // Usually the player or a pivot
    public Transform cam;              // The actual camera (child of this object)
    public LayerMask collisionMask;    // Set in Inspector to ignore floor/player

    public float maxDistance = 1.0f;   // Ideal camera distance
    public float minDistance = 0.34f;   // How close camera can come
    public float smoothSpeed = 10f;    // Lerp speed for smooth motion
    public float camHeightOffset = 0.9f; // How high above the player the ray starts

    private Vector3 camOffset;

    
    void Start()
    {
        // Save camera's local offset (its original "ideal" position)
        camOffset = cam.localPosition;
    }

    void LateUpdate()
    {
        Vector3 rayOrigin = player.position + Vector3.up * camHeightOffset;

        Vector3 desiredCameraWorldPos = transform.TransformPoint(camOffset);
        Vector3 direction = desiredCameraWorldPos - rayOrigin;

        RaycastHit hit;
        float targetDistance = maxDistance;

        if (Physics.Raycast(rayOrigin, direction.normalized, out hit, maxDistance, collisionMask))
        {
            targetDistance = Mathf.Clamp(hit.distance - 0.1f, minDistance, maxDistance);
        }

        Vector3 finalCamPosition = rayOrigin + direction.normalized * targetDistance;
        cam.position = Vector3.Lerp(cam.position, finalCamPosition, Time.deltaTime * smoothSpeed);

        // Optional: camera always looks at upper body/head
        cam.LookAt(player.position + Vector3.up * camHeightOffset);
    }
}
