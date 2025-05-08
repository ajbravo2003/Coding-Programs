using UnityEngine;
using UnityEngine.AI;
using TMPro; // Make sure you have this namespace for TextMeshPro

public class ZombiePatrol : MonoBehaviour
{
    public Transform[] waypoints; // Array to hold the 4 waypoints
    public float patrolSpeed = 2f; // Speed of the zombie when patrolling

    // Added attack variables:
    public Transform player;        
    public float attackRange = 2f;    
    public float attackCooldown = 2f; 
    public TextMeshProUGUI gameOverText;

    private int currentWaypointIndex = 0;
    private NavMeshAgent agent;
    private float attackTimer = 0f;
    private Animator anim;
    
    public HealthBar status;

    public ZombieHealthBar zombieHealth; // Ref to the zombie's health component

    private bool isDead = false;

    public GameObject restartButton;
    

    void Start()
    {
        Time.timeScale = 1f; 
        agent = GetComponent<NavMeshAgent>();
        agent.stoppingDistance = 1.0f;//distance to stop from player
        anim = GetComponent<Animator>(); //gets animation components
        agent.speed = patrolSpeed;

        if (waypoints.Length > 0)
        {
            agent.SetDestination(waypoints[currentWaypointIndex].position); //start patrolling to the first waypoint
        }
    }

    void Update()
    {
        if (isDead) return;

        // Check if zombie's health is 0 or below
        if (zombieHealth.GetCurrentHealth() <= 0f)
        {
            Die();
            
            return;
        }

        // Update the attack timer
        if (attackTimer > 0)
        {
            attackTimer -= Time.deltaTime;
        }

        // Check if the player is assigned and within the attack range
        if (player != null)
        {
            if(status.currentHealth <= 0 ){
                TriggerGameOver();
            }

            float distanceToPlayer = Vector3.Distance(transform.position, player.position);
            if (distanceToPlayer <= attackRange)
            {
                // Switch to attack mode: follow the player
                anim.SetTrigger("Scream"); 
                anim.SetTrigger("Run");
                if (distanceToPlayer <= 1)
                {
                    anim.SetTrigger("handAttack");
                    
                    if (attackTimer <= 0f)
                    {
                        Debug.Log("Zombie attacks the player!");
                        status.TakeDamage(10);
                        attackTimer = attackCooldown;
                    }
                }
                agent.SetDestination(player.position);
                return; 
            }
        }        

        if (agent.remainingDistance <= agent.stoppingDistance)//handles patrol logic
        {
            anim.SetTrigger("Walk");//makes zombies to walk
            currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.Length;//goes to next waypoint
            agent.SetDestination(waypoints[currentWaypointIndex].position);
        }
    }
    // Trigger the Game Over UI
    private void TriggerGameOver()
    {
        if (gameOverText != null)
        {
            gameOverText.enabled = true; // Enable the Game Over text
        }

        Time.timeScale = 0f; // Freeze time (game pause)
        if (restartButton != null)
        {
            restartButton.SetActive(true);
        }
    }
    private void Die()
    {
        isDead = true;
        agent.isStopped = true;
        anim.SetTrigger("Death"); 
        GetComponent<Collider>().enabled = false;//removes colider so u dont lose health
        Invoke("DestroyAfterDeath", 5f);
    }

    private void DestroyAfterDeath()
    {
        Destroy(gameObject);
    }
}
