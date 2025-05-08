using UnityEngine;

public class BatAttack : MonoBehaviour
{
    public int damage = 35;
    private bool canDamage = false;
    private Animator batAnim;

    void awake(){
        batAnim = GetComponent<Animator>();//gets animator
    }

    void OnTriggerEnter(Collider other)
    {
        Debug.Log("Check");
        Debug.Log(canDamage);
        if (canDamage && other.CompareTag("Zombie"))
        {
            Debug.Log("Hit");
            ZombieHealthBar zombie = other.GetComponentInChildren<ZombieHealthBar>();
            if (zombie != null)
            {
                Debug.Log("Check");
                Animator zombieAnim = other.GetComponentInParent<Animator>();
                if (zombieAnim != null)
                {
                    zombieAnim.SetTrigger("Hit");
                }
                zombie.TakeDamage(damage);
                DisableDamage();
            }
        }
    }

    public void EnableDamage()
    {
        canDamage = true;
    }

    public void DisableDamage()
    {
        canDamage = false;
    }
}
