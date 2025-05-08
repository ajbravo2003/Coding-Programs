using UnityEngine;
using UnityEngine.UI;

public class ZombieHealthBar : MonoBehaviour
{
    public Image fillImage;

    public float maxHealth = 100f;
    private float currentHealth;

    private Transform cam;

    void Start()
    {
        cam = Camera.main.transform;
        currentHealth = maxHealth;
        UpdateHealthBar();
    }

    void Update()
    {
        // Make health bar always face the camera
        transform.LookAt(transform.position + cam.forward);
    }

    public void TakeDamage(float amount)
    {
        currentHealth = Mathf.Clamp(currentHealth - amount, 0, maxHealth);
        UpdateHealthBar();
    }

    public void Heal(float amount)
    {
        currentHealth = Mathf.Clamp(currentHealth + amount, 0, maxHealth);
        UpdateHealthBar();
    }

    private void UpdateHealthBar()
    {
        if (fillImage != null)
        {
            fillImage.fillAmount = currentHealth / maxHealth;
        }
    }

    public float GetCurrentHealth()
    {
        return currentHealth;
    }
}
