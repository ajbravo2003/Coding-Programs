using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class PlayerLight : MonoBehaviour
{
    public Transform player;
    public Vector3 offset = new Vector3(0, 2, 0);

    void LateUpdate()
    {
        transform.position = player.position + offset;
    }
}
