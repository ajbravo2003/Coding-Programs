using UnityEngine;

public class BreakableBoard : MonoBehaviour
{
    private HingeJoint hinge;
    private bool isBroken = false;

    void Start()
    {
        hinge = GetComponent<HingeJoint>();
    }

    void OnCollisionEnter(Collision collision)
    {
        if (isBroken) return;

        if (collision.gameObject.CompareTag("Player"))
        {
            float impactForce = collision.relativeVelocity.magnitude;

            if (impactForce > 5f)
            {
                BreakBoard();
            }
        }
    }

    void BreakBoard()
    {
        isBroken = true;
        Destroy(hinge); 
        Rigidbody rb = GetComponent<Rigidbody>();
        rb.AddTorque(Random.onUnitSphere * 10f, ForceMode.Impulse);
    }
}
