using UnityEngine;
using System.Collections;

public class PlayerAnimation : MonoBehaviour
{
    public PlayerInfection PlayerInfection;
    public PlayerMovement PlayerMovement;
    public float agonyDuration = 2.7f;
    private Animator anim;
    private float moveInputX;
    private float moveInputY;
    public Inventory inventory;
    private int lastAgonyTrigger = 0;

    void Start()
    {
        anim = GetComponent<Animator>();
    }

    IEnumerator WaitForSwingThenReset()
    {
        anim.SetBool("Swing", true);

        yield return new WaitUntil(() => anim.GetCurrentAnimatorStateInfo(0).IsName("Swing"));
        yield return new WaitWhile(() => anim.GetCurrentAnimatorStateInfo(0).normalizedTime < 1f);

        anim.SetBool("Swing", false);
    }

    void Update()
    {
        moveInputX = Input.GetAxisRaw("Horizontal");
        moveInputY = Input.GetAxisRaw("Vertical");

        // Set weapon state
        if (inventory.currentItem == 1)
        {
            anim.SetBool("hasMelee", true);
            anim.SetBool("hasGun", false);
            anim.SetBool("hasConsumable", false);
        }
        else if (inventory.currentItem == 2)
        {
            anim.SetBool("hasMelee", false);
            anim.SetBool("hasGun", true);
            anim.SetBool("hasConsumable", false);
        }
        else if (inventory.currentItem == 3 || inventory.currentItem == 4 || inventory.currentItem == 5)
        {
            anim.SetBool("hasMelee", false);
            anim.SetBool("hasGun", false);
            anim.SetBool("hasConsumable", true);
        }
        else
        {
            anim.SetBool("hasMelee", false);
            anim.SetBool("hasGun", false);
            anim.SetBool("hasConsumable", false);
        }

        if (Input.GetKeyDown(KeyCode.Mouse0) && inventory.currentItem == 1 && !inventory.meleeOnCooldown)
        {
            StartCoroutine(WaitForSwingThenReset());
        }

        // Movement animations
        anim.SetBool("isRunning", moveInputY != 0);
        anim.SetBool("StrafeLeft", moveInputX < -0.1f);
        anim.SetBool("StrafeRight", moveInputX > 0.1f);

        // Jumping
        if (Input.GetKeyDown(KeyCode.Space) && PlayerMovement.isGrounded)
        {
            anim.SetTrigger("isJumping");
        }

        // Infection-based agony trigger
        if ((int)PlayerInfection.currentInfection / 10 > lastAgonyTrigger)
        {
            lastAgonyTrigger = (int)PlayerInfection.currentInfection / 10;

            if (anim != null)
            {
                anim.SetTrigger("infection_10");
            }

            if (PlayerMovement != null)
            {
                PlayerMovement.canControl = false;
                StartCoroutine(WaitForAgonyToFinish());
            }
             // Start coroutine to re-enable control
            
        }

        //DO NOT re-enable control here! Leave that to EndAgony().
    }

    private IEnumerator WaitForAgonyToFinish()
{
    yield return new WaitForSeconds(agonyDuration); // Replace with your animation length in seconds

    if (PlayerMovement != null)
    {
        PlayerMovement.canControl = true;
    }
}

}
