using UnityEngine;
using UnityEngine.UI;  

public class HealthBar : MonoBehaviour
{
    public PlayerInfection PlayerInfection;
    public Image healthBarImage; //health bar
    public Image infectionBarImage; //infection bar
    public float maxHealth = 100f;
    public float currentHealth;
    public float maxInfection = 100f;  // Max infection amount

    [Header("Damage Overlay")]
    public Image overlay; //DamageOverlay gameobj
    public float duration;
    public float fadeSpeed;
    private float durationTimer;
    // Infection variables
    

    public AudioSource damageAudioSource;  // Reference to the AudioSource
    public AudioClip damageSound;  // Reference to the sound clip to play on damage

    void Start()
    {
        currentHealth = maxHealth;  // Initialize the health
        UpdateHealthBar();  //Update health bar to match the initial health
        UpdateInfectionBar(0);  //start infection at 0
        overlay.color = new Color(overlay.color.r, overlay.color.g, overlay.color.b, 0); //start with no dmg overlay
    }

    void Update()//fade dmg overlay
    {
        if (overlay.color.a > 0)
        {
            durationTimer += Time.deltaTime;
            if (durationTimer > duration)
            {
                //fade image out
                float tempAlpha = overlay.color.a;
                tempAlpha -= Time.deltaTime * fadeSpeed;
                overlay.color = new Color(overlay.color.r, overlay.color.g, overlay.color.b, tempAlpha);
            }
        }
    }
    public void TakeDamage(float damage)//function that will decrease health when button is clicked
    {
        currentHealth -= damage;
        currentHealth = Mathf.Clamp(currentHealth, 0f, maxHealth);  // Ensure health doesn't go below 0
        UpdateHealthBar();  // Update the health bar
        if (currentHealth <= 0f)
        {
            StopInfection();  //Stop the infection when the player dies
            PlayerInfection.TriggerGameOver();
        }
        //flash damage overlay
        durationTimer = 0;
        overlay.color = new Color(overlay.color.r, overlay.color.g, overlay.color.b, 0.32f);
        
        if (damageAudioSource != null && damageSound != null)
        {
            damageAudioSource.PlayOneShot(damageSound);  // Play the damage sound clip once
        }
    }

    public void StartInfection()
    {
        // PlayerInfection.currentInfection += 10f;  //
        // PlayerInfection.currentInfection = Mathf.Clamp(PlayerInfection.currentInfection, 0f, maxInfection);  

        // if (PlayerInfection.currentInfection >= maxInfection)
        // {
        //     ApplyInfectionDamage();//applies infection damage
        // }

        // UpdateInfectionBar(PlayerInfection.currentInfection);//updates infection bar filling
    }

    public void StopInfection()
    {
        PlayerInfection.currentInfection = 0f;
        UpdateInfectionBar((int)PlayerInfection.currentInfection);//fixes filling to empty
    }

    public void UpdateHealthBar()
    {
        // Set the fill amount based on the current health
        healthBarImage.fillAmount = currentHealth / maxHealth;
    }

    // Function to update the infection bar fill amount
    public void UpdateInfectionBar(float infection)
    {
        // Set the fill amount based on current infection
        //PlayerInfection.PlayerInfection.currentInfection = infection;
        infectionBarImage.fillAmount =  infection / maxInfection;
    }

    private void ApplyInfectionDamage() //damage is inflicted when we have max infection rate
    {
        currentHealth -= 10f;
        currentHealth = Mathf.Clamp(currentHealth, 0f, maxHealth);  
        UpdateHealthBar();  

        if (currentHealth <= 0f)
        {
            StopInfection();  //Stop the infection when the player dies
            PlayerInfection.TriggerGameOver();
        }
    }
}
