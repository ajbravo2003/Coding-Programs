using System.Collections.Generic;
using UnityEngine;

public class CompanionAI : MonoBehaviour
{
    // Existing variables
    public Transform player;
    public Transform[] foodLocations;
    private float hunger = 0f;
    private enum State { Idle, Scavenge, FollowPlayer }
    private State currentState = State.Idle;

    // A* Pathfinding variables
    List<Node> currentPath = new List<Node>();
    int pathIndex = 0;
    public Pathfinding pathfinder;

    void Start()
    {
        // Set up pathfinding system
        pathfinder = FindAnyObjectByType<Pathfinding>();


        // You can customize which state you start in
        currentState = State.FollowPlayer; // Example: start by following the player
    }

    void Update()
    {
        // FSM for Companion states
        switch (currentState)
        {
            case State.Scavenge:
                Transform target = FindClosestFood();
                if (target != null)
                    FollowPathTo(target.position);
                break;
            case State.FollowPlayer:
                if (player != null)
                    FollowPathTo(player.position);
                break;
            case State.Idle:
                // Companion is idle, do nothing or wander
                break;
        }

        // Handle hunger
        hunger += Time.deltaTime * 0.01f;
        hunger = Mathf.Clamp01(hunger);
    }

    // Function to find the closest food location (or objective)
    Transform FindClosestFood()
    {
        Transform closestFood = null;
        float closestDistance = Mathf.Infinity;

        foreach (Transform food in foodLocations)
        {
            float distance = Vector3.Distance(transform.position, food.position);
            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestFood = food;
            }
        }

        return closestFood;
    }

    // A* Pathfinding - Move towards a target position
    void FollowPathTo(Vector3 targetPos)
    {
        // Check if we already have a valid path to follow
        if (currentPath.Count == 0 || Vector3.Distance(currentPath[currentPath.Count - 1].worldPosition, targetPos) > 1f)
        {
            // Calculate the new path
            currentPath = pathfinder.FindPath(transform.position, targetPos);
            pathIndex = 0;
        }

        // Move along the path
        if (currentPath != null && pathIndex < currentPath.Count)
        {
            // Get the target position from the path
            Vector3 target = currentPath[pathIndex].worldPosition;

            // Move the companion to the target position
            transform.position = Vector3.MoveTowards(transform.position, target, Time.deltaTime * 2f);

            // Check if we've reached the current node in the path
            if (Vector3.Distance(transform.position, target) < 0.1f)
            {
                pathIndex++;
            }
        }
    }

    // Debugging: visualize the path in the scene view (optional)
    void OnDrawGizmos()
    {
        if (currentPath != null)
        {
            for (int i = pathIndex; i < currentPath.Count; i++)
            {
                Gizmos.color = Color.green;
                Gizmos.DrawSphere(currentPath[i].worldPosition, 0.2f);
            }
        }
    }
}
