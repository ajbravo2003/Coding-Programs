using UnityEngine;

public class Pickup : MonoBehaviour
{

    public HealthBar status;
    public Inventory inventory;
    public NPC npcReference;
    public Animator npcAnim;
    private void OnCollisionEnter (Collision collision)
    {
        Destroy(gameObject);

        if(gameObject.tag == "Side1")
        {
            Debug.Log("Side 1 done");
            npcAnim.SetBool("Dead", true);
            Destroy(npcReference);
            Collider col = npcReference.GetComponent<Collider>();
            if (col != null) col.enabled = false;
            return;
        }

        if(gameObject.tag == "Food")
        {
            Debug.Log("Food Picked up");
            inventory.food += 1;
            inventory.UpdateItemCount();
        }
        else if(gameObject.tag == "Ammo")
        {
            Debug.Log("Ammo Picked up");
            inventory.ammo += 6;
            inventory.UpdateItemCount();
        }
        else if(gameObject.tag == "Syringe")
        {
            Debug.Log("Stabilizer Picked up");
            inventory.stabilizers += 1;
            inventory.UpdateItemCount();
        }
        else if (gameObject.tag == "Bat")
        {
            Debug.Log("Bat picked up");
            inventory.hasMelee = true;
        }
        else if (gameObject.tag == "Gun")
        {
            Debug.Log("Gun picked up");
            inventory.hasGun = true;
        }
        inventory.ItemPickupSound();
        inventory.UpdateImages();
    }
}
