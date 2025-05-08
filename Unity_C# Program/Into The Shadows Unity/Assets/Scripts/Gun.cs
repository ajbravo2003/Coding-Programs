using UnityEngine;
using System.Collections;

public class Gun : MonoBehaviour
{
    public Camera playerCamera;
    public float shootCooldown = 0.5f;
    public float shootRange = 100f;
    public int damage = 10;
    public LayerMask targetMask;
    public ParticleSystem muzzleFlash;
    public AudioSource audioSource;
    public AudioClip shotSound;

    private bool canShoot = true;

    void Update()
    {
        if (Input.GetMouseButtonDown(0) && canShoot)
        {
            StartCoroutine(Shoot());
        }
    }

    private IEnumerator Shoot()
    {
        Debug.Log("Shot");
        canShoot = false;

        muzzleFlash.Play();
        audioSource.volume = 0.02f;
        audioSource.PlayOneShot(shotSound);

        Ray ray = playerCamera.ViewportPointToRay(new Vector3(0.5f, 0.5f, 0));
        RaycastHit hit;

        if (Physics.Raycast(ray, out hit, shootRange, targetMask))
        {
            Debug.Log("Hit: " + hit.collider.name);

            ZombieHealthBar zombie = hit.collider.GetComponentInChildren<ZombieHealthBar>();
            if (zombie != null)
            {
                zombie.TakeDamage(damage);
            }
        }

        yield return new WaitForSeconds(shootCooldown);

        canShoot = true;
    }
}
