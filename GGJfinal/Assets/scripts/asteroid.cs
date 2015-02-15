using UnityEngine;
using System.Collections;

public class asteroid : MonoBehaviour {

	private float astVelocity;
	private GameObject director;
	private GameObject player;

	public GameObject explosion;
	// Use this for initialization
	void Awake(){
		director = GameObject.FindGameObjectWithTag ("Director");
		player = director.GetComponent<GameDirector>().player;
	}
	void Start () {
		transform.forward = Vector3.Normalize ( new Vector3( Random.Range(-30, 30), Random.Range (-30, 30), 0.0f) );
		astVelocity = Random.Range (-0.5f, +0.5f);
		Destroy (gameObject, 5.0f);

	}
	
	// Update is called once per frame
	void Update () {
		transform.position += astVelocity*transform.forward;
	}

	public void setForward(GameObject _player){

		transform.forward = (-1.0f)*(_player.transform.forward);


	}

	public void OnExplode(){
		// Create a quaternion with a random rotation in the z-axis.
		Quaternion randomRotation = Quaternion.Euler(0f, 0f, Random.Range(0f, 360f));
		// Instantiate the explosion where the rocket is with the random rotation.
		GameObject explo = (GameObject) Instantiate(explosion, transform.position, randomRotation);
		Destroy (explo, 3.0f);
		Destroy (gameObject);
	}
	
	void OnTriggerEnter(Collider col){
		//	Debug.Log (col.tag);
		OnExplode ();
		//	director.GetComponent<GameDirector>().gamePuase();
	}

}
