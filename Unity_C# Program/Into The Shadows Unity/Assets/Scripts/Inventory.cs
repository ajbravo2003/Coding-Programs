using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System.Collections;

public class Inventory : MonoBehaviour
{
    public Camera mainCamera;
    public Camera adsCamera;
    public Camera hitscanCamera;
    Rigidbody rb;
    public HealthBar status;
    public BatAttack bat;
    public GameObject[] itemsInHand;
    public Transform hotbarParent;
    public TMP_Text foodAmount;
    public TMP_Text stabilizerAmount;
    public TMP_Text ammoAmount;
    private RectTransform[] hotbarSlots;
    public GameObject healthEffectParticles;
    public GameObject stabilizerEffectParticles;
    public Transform effectSpawnPoint;
    public AudioSource audioSource;
    public AudioClip consumableSound;
    public LayerMask targetMask;
    public ParticleSystem muzzleFlash;
    public AudioClip shotSound;
    public AudioClip emptyGunSound;
    public Canvas mapDisplay;
    public bool hasMelee;
    public bool hasGun;
    public bool hasMap;
    public int food;
    public int stabilizers;
    public int ammo;
    private Color normalColor;
    private Color noneColor;
    private Color highlight;
    private Color errorColor;
    private float scale = 1.2f;
    public int currentItem;
    public Canvas meleeCooldownCanvas;
    public TMP_Text meleeCooldownText;
    public bool meleeOnCooldown = false;
    private float attackCooldown = 1.8f;
    public AudioClip batSwing;
    public Canvas gunCooldownCanvas;
    public TMP_Text gunCooldownText;
    private bool canShoot = true;
    public float shootCooldown = 0.5f;
    public float shootRange = 100f;
    public int gunDamage = 50;
    public AudioClip pickupSound;
    public PlayerInfection PlayerInfection;
    public GameObject crosshair;


    // 1: Melee, 2: Gun, 3: Food, 4: Stabilizers, 5: Ammo 6: Map
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        adsCamera.enabled = false;
        hasMelee = false;
        hasGun = false;
        hasMap = false;
        food = 2;
        stabilizers = 0;
        ammo = 0;
        normalColor = new Color32(255,255,110,100);
        noneColor = new Color32(103,103,103,100);
        highlight = new Color32(0,255,255,100);
        errorColor = Color.red;
        hotbarSlots = new RectTransform[5];
        currentItem = -1;
        for (int i = 0; i < 5; i++)
        {
            hotbarSlots[i] = hotbarParent.GetChild(i).GetComponent<RectTransform>();
        }
        UpdateItemCount();
    }

    void Update()
    {
        if(currentItem == 2)
        {
            crosshair.SetActive(true);
        }
        else
        {
            crosshair.SetActive(false);
        }

        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            Debug.Log("Pressed 1");
            EquipItem(1);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            Debug.Log("Pressed 2");
            EquipItem(2);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            Debug.Log("Pressed 3");
            EquipItem(3);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha4))
        {
            Debug.Log("Pressed 4");
            EquipItem(4);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha5))
        {
            Debug.Log("Pressed 5");
            EquipItem(5);
        }
        else if (Input.GetKeyDown(KeyCode.M))
        {
            Debug.Log("Pressed M");
            EquipItem(5);
        }
        else if (Input.GetKeyDown(KeyCode.Mouse0))
        {
            UseItem();
        }
        else if (Input.GetKeyDown(KeyCode.Return))
        {
            mapDisplay.gameObject.SetActive(false);
        }
        else if (Input.GetMouseButtonDown(1) && currentItem == 2)
        {
            mainCamera.enabled = false;
            adsCamera.enabled = true;
        }
        else if (Input.GetMouseButtonUp(1)  && currentItem == 2)
        {
            mainCamera.enabled = true;
            adsCamera.enabled = false;
        }

        float scroll = Input.GetAxis("Mouse ScrollWheel");
        int equip = 0;

        if (scroll < 0f)
        {
            Debug.Log("Scroll Down");
            mapDisplay.gameObject.SetActive(false);

            if (currentItem + 1 > 5)
            {
                equip = 1;
            }
            else
            {
                equip = currentItem + 1;
            }
            
            EquipItem(equip);
        }
        else if (scroll > 0f)
        {
            Debug.Log("Scroll Up");
            mapDisplay.gameObject.SetActive(false);

            if (currentItem - 1 < 1)
            {
                equip = 5;
            } 
            else
            {
                equip = currentItem - 1;
            }
            
            EquipItem(equip);
        }
    }

    IEnumerator MeleeAttackCooldownTimer()
    {
        meleeOnCooldown = true;
        bat.EnableDamage();
        audioSource.volume = 0.3f;
        audioSource.PlayOneShot(batSwing);

        meleeCooldownCanvas.gameObject.SetActive(true);
        float timeRemaining = attackCooldown;

        var image = hotbarSlots[0].GetComponent<Image>();

        if (image != null) image.color = normalColor;

        while (timeRemaining > 0)
        {
            timeRemaining -= Time.deltaTime;
            meleeCooldownText.text = Mathf.Max(timeRemaining, 0).ToString("F2");
            yield return null;
        }
        if (image != null) image.color = highlight;

        meleeCooldownCanvas.gameObject.SetActive(false);
        meleeOnCooldown = false;
        bat.DisableDamage();
    }

    private IEnumerator Shoot()
    {
        Debug.Log("Shot");
        canShoot = false;
        ammo -= 1;
        UpdateItemCount();

        muzzleFlash.Play();
        audioSource.volume = 0.1f;
        audioSource.PlayOneShot(shotSound);

        gunCooldownCanvas.gameObject.SetActive(true);
        float timeRemaining = shootCooldown;

        Ray ray = hitscanCamera.ViewportPointToRay(new Vector3(0.5f, 0.5f, 0));
        RaycastHit hit;

        if (Physics.Raycast(ray, out hit, shootRange, targetMask))
        {
            Debug.Log("Hit: " + hit.collider.name);

            ZombieHealthBar zombie = hit.collider.GetComponentInChildren<ZombieHealthBar>();
            if (zombie != null)
            {
                zombie.TakeDamage(gunDamage);
            }
        }

        var image = hotbarSlots[1].GetComponent<Image>();

        if (image != null) image.color = normalColor;

        while (timeRemaining > 0)
        {
            timeRemaining -= Time.deltaTime;
            gunCooldownText.text = Mathf.Max(timeRemaining, 0).ToString("F2");
            yield return null;
        }

        if (image != null) image.color = highlight;

        gunCooldownCanvas.gameObject.SetActive(false);
        canShoot = true;
    }

    public void ItemPickupSound()
    {
        audioSource.volume = 0.3f;
        audioSource.PlayOneShot(pickupSound);
    }

    void UseItem()
    {
        Debug.Log(currentItem);
        switch (currentItem)
        {
            
            case 1:
                if (hasMelee && !meleeOnCooldown)
                {
                    Debug.Log("Swing");
                    StartCoroutine(MeleeAttackCooldownTimer());
                }
                break;
            case 2:
                if (canShoot && ammo > 0)
                {
                    StartCoroutine(Shoot());
                }
                else if (ammo == 0)
                {
                    audioSource.volume = 0.1f;
                    audioSource.PlayOneShot(emptyGunSound);
                }
                break;
            case 3:
                Debug.Log("Check");
                if (food > 0)
                {
                    PlayConsumableEffects(0);
                    food--;
                    if (status.currentHealth + 50 > status.maxHealth)
                    {
                        status.currentHealth = status.maxHealth;
                    }
                    else
                    {
                        status.currentHealth += 50;
                    }
                    status.UpdateHealthBar();
                    UpdateItemCount();
                }
                break;
            case 4:
                Debug.Log("Check");
                if (stabilizers > 0)
                {
                    PlayConsumableEffects(1);
                    stabilizers--;
                    if (PlayerInfection.currentInfection - 35 < 0)
                    {
                        status.UpdateInfectionBar(0);
                    }
                    else
                    {
                        status.UpdateInfectionBar(-35);
                    }
                    
                    UpdateItemCount();
                }
                break;
            case 5:
                if (hasMap)
                {
                    mapDisplay.gameObject.SetActive(true);
                }
                break;
        }
    }

    void PlayConsumableEffects(int effect)
    {
        if (effect == 0)
        {
            Vector3 spawnOffset = new Vector3(-0.5f, 0f, 0f);
            var effect1 = Instantiate(healthEffectParticles, effectSpawnPoint.position + spawnOffset, Quaternion.identity, effectSpawnPoint);
            Destroy(effect1, 3f);
        }
        else 
        {
            Vector3 spawnOffset = new Vector3(-0.5f, 0f, 0f);
            var effect2 = Instantiate(stabilizerEffectParticles, effectSpawnPoint.position + spawnOffset, Quaternion.identity, effectSpawnPoint);
            Destroy(effect2, 3f);
        }

        if (audioSource != null && consumableSound != null)
        {
            audioSource.volume = 0.1f;
            audioSource.PlayOneShot(consumableSound);
        }
    }


    bool hasItem(int key)
    {
        switch (key)
        {
            case 1:
                if (!hasMelee)
                {
                    return false;
                }
                break;
            case 2:
                if (!hasGun)
                {
                    return false;
                }
                break;
            case 3:
                if (food == 0)
                {
                    return false;
                }
                break;
            case 4:
                if (stabilizers == 0)
                {
                    return false;
                }
                break;
            case 5:
                if (!hasMap)
                {
                    return false;
                }
                break;
        }
        return true;
    }

    public void UpdateImages()
    {
        for (int i = 0; i < hotbarSlots.Length; i++)
        {
            var image = hotbarSlots[i].GetComponent<Image>();

            if (i == (currentItem))
            {
                continue;
            }
            else
            {
                if (image != null)
                {
                    if (hasItem(i + 1))
                    {
                        image.color = normalColor;
                    }
                    else
                    {
                        image.color = noneColor;
                    }
                }
            }
        }
    }

    private IEnumerator FlashRed(RectTransform slot, Image image)
    {
        if (image == null) yield break;

        image.color = errorColor;

        float flashDuration = 1f; 
        float elapsed = 0f;

        while (elapsed < flashDuration)
        {
            elapsed += Time.deltaTime;
            float t = elapsed / flashDuration;
            
            image.color = Color.Lerp(errorColor, noneColor, t);

            yield return null;
        }

        image.color = noneColor;
    }


    void EquipItem(int key){
        for (int i = 0; i < hotbarSlots.Length; i++)
        {
            var image = hotbarSlots[i].GetComponent<Image>();
            
            if (i == (key - 1))
            {
                if (!hasItem(key))
                {
                    StartCoroutine(FlashRed(hotbarSlots[i], image));
                    currentItem = -1;
                    continue;
                }
                if(key == currentItem) // Unequip current item
                {
                    hotbarSlots[i].localScale = Vector3.one * 1;
                    image.color = normalColor;
                    itemsInHand[i].SetActive(false);
                    currentItem = -1;
                }
                else // Equip chosen item
                {
                    hotbarSlots[i].localScale = Vector3.one * scale;
                    if (image != null) image.color = highlight;

                    itemsInHand[i].SetActive(true);
                    
                    currentItem = key;
                }
            }
            else // Reset state of other items
            {
                hotbarSlots[i].localScale = Vector3.one * 1;
                if (image != null)
                {
                    if (hasItem(i + 1))
                    {
                        image.color = normalColor;
                    }
                    else
                    {
                        image.color = noneColor;
                    }
                }
                itemsInHand[i].SetActive(false);
            }
        }
    }

    public void UpdateItemCount()
    {
        foodAmount.text = food.ToString();
        stabilizerAmount.text = stabilizers.ToString();
        ammoAmount.text = ammo.ToString();
    }
}
