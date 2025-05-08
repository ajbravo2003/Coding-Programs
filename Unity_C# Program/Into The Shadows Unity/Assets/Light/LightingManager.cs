using UnityEngine;

public class LightingManager : MonoBehaviour
{
    [Header("References")]
    public Light sunLight;                   // Assign your Directional Light here
    public Transform player;                 // Assign your Player's Transform

    [Header("Infection Settings")]
    public float infectionRate = 2.0f;         // Infection increase per second in sunlight
    //public float currentInfection = 0f;      // Optional: track infection over time
    public float maxInfection = 100f;

    [Header("Raycast Settings")]
    public LayerMask obstructionMask;        // Set to "Environment" or what blocks sun
    public float rayOriginHeight = 0.0f;     // Height from player position to cast from
    public PlayerInfection PlayerInfection;
    void Update()
    {
        if (IsInDirectSunlight())
        {
            PlayerInfection.IncreaseInfection(infectionRate * Time.deltaTime);
        }
    }

    bool IsInDirectSunlight()
    {
        if (sunLight == null || player == null) return false;

        // Direction light is shining FROM (cast a ray TOWARD the sun)
        Vector3 sunDirection = -sunLight.transform.forward;

        // Start from above the player's head
        Vector3 rayOrigin = player.position + Vector3.up * rayOriginHeight;

        // Check for obstructions between player and sun
        if (Physics.Raycast(rayOrigin, sunDirection, out RaycastHit hit, Mathf.Infinity, obstructionMask))
        {
            Debug.DrawRay(rayOrigin, sunDirection * 5f, Color.red); // Obstructed
            return false;
        }

        Debug.DrawRay(rayOrigin, sunDirection * 5f, Color.green); // In sun
        return true;
    }
}
