using UnityEngine;
using System.Collections;
public enum NPCState {
    Idle,
    TrackingPlayer,
    DialogueFear,
    DialogueUneasy,
    DialogueEmpathy,
    DialoguePostItemUse,
    DialogueNeutral,
    Intro
}
public enum NPCType { 
    StartNPC,
    Side1NPC,
    Side2NPC,
}
public class NPC : MonoBehaviour
{
    private bool isPlayerNearby = false;
    private Transform nearbyPlayer;
    public HealthBar status;
    public NPCState currentState;
    private Animator animator;
    private Coroutine currentAnimRoutine;
    public Canvas tooltip;
    public bool intro;
    public Inventory inventory;
    public NPCType npcType;
    private int stage = 0;

    private bool hasGivenItem = false;
    private bool respondedToItemUse = false;

    void Start()
    {
        animator = GetComponent<Animator>();
        intro = false;
    }

    void Update()
    {
        CheckPlayerDistance();

        if (isPlayerNearby)
        {
            Vector3 targetDirection = nearbyPlayer.position - transform.position;
            targetDirection.y = 0;

            if (targetDirection != Vector3.zero && npcType == NPCType.StartNPC)
            {
                Quaternion targetRotation = Quaternion.LookRotation(targetDirection);
                transform.rotation = Quaternion.Slerp(transform.rotation, targetRotation, Time.deltaTime * 5f);
            }

            tooltip.enabled = true;
            
            if (Input.GetKeyDown(KeyCode.E))
            {

                Debug.Log("Hovered and Pressed E");
                UpdateStateBasedOnPlayer();
            }
            
        }
        else
        {
            tooltip.enabled = false;
        }
        
    }

    void CheckPlayerDistance()
    {
        GameObject playerObj = GameObject.FindGameObjectWithTag("Player");

        if (playerObj == null) return;

        float distance = Vector3.Distance(transform.position, playerObj.transform.position);

        if (distance < 2.5)
        {
            isPlayerNearby = true;
            nearbyPlayer = playerObj.transform;
        }
        else
        {
            isPlayerNearby = false;
            nearbyPlayer = null;
        }
    }

    void StartNPCState(){
        if(!intro)
        {
            currentState = NPCState.Intro;
            intro = true;
        }
        else if (PlayerInfection.currentInfection >= 80f)
        {
            currentState = NPCState.DialogueFear;
        }
        else if (status.currentHealth < 50f && !hasGivenItem)
        {
            currentState = NPCState.DialogueEmpathy;
        }
        else if (PlayerInfection.currentInfection >= 50f)
        {
            currentState = NPCState.DialogueUneasy;
        }
        else if (hasGivenItem && !respondedToItemUse)
        {
            currentState = NPCState.DialoguePostItemUse;
            respondedToItemUse = true;
        }
        else
        {
            currentState = NPCState.DialogueNeutral;
        }
    }

    void UpdateStateBasedOnPlayer()
    {
        if(nearbyPlayer == null){
            Debug.Log("Player missing error");
            return;
        }
        else if(status == null){
            Debug.Log("Status missing error");
            return;
        }

        if (npcType == NPCType.StartNPC)
        {
            StartNPCState();
            HandleAnimations();
            HandleDialogue();
        }
        else if (npcType == NPCType.Side1NPC)
        {
            Debug.Log(stage);
            switch (stage)
            {
                case 0:
                    ShowDialogue("Holy shit, you aren't a zombie? Did you get past the ones on the street earlier?");
                    stage += 1;
                    break;
                case 1:
                    ShowDialogue("Hey, I've got a favor to ask of you. Would you hear me out?");
                    stage += 1;
                    break;
                case 2:
                    ShowDialogue("I got separated from my son, Bobby, and I need to make sure he is okay. He should be in " +
                    "the building at the end of the street past the military truck bloackade you just passed.");
                    stage += 1;
                    break;
                case 3:
                    ShowDialogue("If you keep heading forward along the path on that map of yours, it should be the third blue building marked. " +
                    "Please, can you find my son? It might be too late for me, but he should live on. There are food supplies in that building you can take too.");
                    stage += 1;
                    break;
                case 4:
                    ShowDialogue("Please find my son, I beg you.");
                    break;
                
            }
        }
        else if (npcType == NPCType.Side2NPC)
        {
            if (stage > 2)
            {
                ShowDialogue("You were too late. Bobby is dead.");
                stage = -1;
                return;
            }
            ShowDialogue("This poor child was eaten alive.");
        }
        
    }

    void HandleDialogue()
    {
        switch (currentState)
        {
            case NPCState.Intro:
                ShowDialogue("Hey there. The world's gone to shit, zombies are everywhere and the sun infects you. " +
                "I heard there's a cure in this town, but there's no way I'm leaving this building. Take this map and grab that bat " +
                "if you want to try your luck. Take care.");
                inventory.hasMap = true;
                inventory.UpdateImages();
                break;
            case NPCState.DialogueFear:
                ShowDialogue("Hey are you infected!? Stay away from me!");
                break;
            case NPCState.DialogueUneasy:
                ShowDialogue("You look a little off... feeling okay? " + "You should look for some items to heal up. " +
                "There are buildings around here you can enter that will have them. Be careful though, there might be zombies gaurding them.");
                break;
            case NPCState.DialogueEmpathy:
                if(hasGivenItem)
                {
                    ShowDialogue("Sorry, I don't have any more things to give you." + " You should look for some items to heal up. " +
                    "There are buildings around here you can enter that will have them. Be careful though, there might be zombies gaurding them.");
                    break;
                }
                GiveHealingItem(nearbyPlayer);
                ShowDialogue("You’re hurt. Here, take this." + " You should look for some items to heal up. " +
                "There are buildings around here you can enter that will have them. Be careful though, there might be zombies gaurding them.");
                break;
            case NPCState.DialoguePostItemUse:
                ShowDialogue("Glad that helped. Be careful.");
                break;
            case NPCState.DialogueNeutral:
                ShowDialogue("You should look for some items to heal up. " +
                "There are buildings around here you can enter that will have them. Be careful though, there might be zombies gaurding them.");
                break;
        }
    }

    void HandleAnimations()
    {
        if (currentAnimRoutine != null)
        {
            StopCoroutine(currentAnimRoutine);
        }
        string animName = "";
        switch (currentState)
        {
            case NPCState.Intro:
                animName = "HandItem";
                break;
            case NPCState.DialogueFear:
                animName = "Fear";
                break;
            case NPCState.DialogueUneasy:
                animName = "Uneasy";
                break;
            case NPCState.DialogueEmpathy:
                animName = hasGivenItem ? "ShakeHead" : "HandItem";
                break;
            case NPCState.DialogueNeutral:
                animName = "Neutral";
                break;
        }
        currentAnimRoutine = StartCoroutine(WaitForAnimationThenReset(animName));
    }


    IEnumerator WaitForAnimationThenReset(string stateName)
    {
        ResetStates();
        animator.SetBool(stateName, true);

        yield return new WaitUntil(() => animator.GetCurrentAnimatorStateInfo(0).IsName(stateName));

        bool interrupted = false;

        while (animator.GetCurrentAnimatorStateInfo(0).normalizedTime < 1f)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                interrupted = true;
                break;
            }
            yield return null;
        }

        animator.SetBool(stateName, false);

        animator.SetBool("IsIdle", true);
        yield return null;

        animator.SetBool("IsIdle", false);

        if (interrupted)
        {
            UpdateStateBasedOnPlayer();
        }
    }

    void ResetStates()
    {
        animator.SetBool("IsIdle", false);
        animator.SetBool("HandItem", false);
        animator.SetBool("ShakeHead", false);
        animator.SetBool("Fear", false);
        animator.SetBool("Uneasy", false);
        animator.SetBool("Neutral", false);
    }

    void ShowDialogue(string text)
    {
        if (DialogueUI.Instance == null)
    {
        Debug.LogError("DialogueUI.Instance is null!");
        return;
    }
        DialogueUI.Instance.ShowDialogue(text);
    }

    void GiveHealingItem(Transform player)
    {
        hasGivenItem = true;
        Debug.Log("NPC gave healing item");
        // Inventory logic to be implemented
        inventory.food += 1;
        inventory.UpdateItemCount();
        inventory.UpdateImages();
    }
}
