using UnityEngine;

public class Audio : StateMachineBehaviour
{
    public AudioClip sound;
    private AudioSource audioSource;

    public override void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        audioSource = animator.GetComponent<AudioSource>();
        if (audioSource && sound)
        {
            audioSource.clip = sound;
            audioSource.loop = false; 
            audioSource.Play();
        }
    }

    public override void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        if (audioSource && audioSource.clip == sound)
        {
            audioSource.Stop();
            audioSource.clip = null;
        }
    }
}
