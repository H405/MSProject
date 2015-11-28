//==============================================================================
//
// File   : SceneSplash.h
// Brief  : �X�v���b�V���V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_SCENE_SPLASH_H
#define MY_SCENE_SPLASH_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../system/SceneMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class CameraObject;
class CameraStateSpline;
class LightDirection;
class LightPoint;
class ManagerPoint;
class Material;
class Object2D;
class ObjectBillboard;
class ObjectMesh;
class ObjectModel;
class ObjectModelMaterial;
class ObjectRiver;
class ObjectSkinMesh;
class ObjectSky;

//******************************************************************************
// �N���X��`
//******************************************************************************
class SceneSplash : public SceneMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	SceneSplash( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~SceneSplash( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : SceneArgumentMain* pArgument		: �V�[������
	//==============================================================================
	int Initialize( SceneArgumentMain* pArgument );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : SceneArgumentMain* pArgument		: �V�[������
	//==============================================================================
	int Reinitialize( SceneArgumentMain* pArgument );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : SceneSplash* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( SceneSplash* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

protected:

private:
	void InitializeSelf( void );
	SceneSplash( const SceneSplash& );
	SceneSplash operator=( const SceneSplash& );

	CameraObject*				pCamera_;						// �ʏ�J����
	CameraObject*				pCameraShadow_;					// �e�p�J����
	LightDirection*				pLight_;						// ���C�g
	LightPoint**				ppPointLight_;					// �|�C���g���C�g

	ManagerPoint*				pPoint_;						// �|�C���g�X�v���C�g�Ǘ��N���X

	static const int			COUNT_MODEL = 10;				// ���f����

	Object2D*					pObject2D_;						// 2D�I�u�W�F�N�g
	ObjectMesh*					pObjectMesh_;					// ���b�V��
	ObjectSky*					pObjectSky_;					// �X�J�C�h�[��
	ObjectModel*				pObjectModel_;					// ���f��
	ObjectModelMaterial*		pObjectModelMaterial_;			// �e�N�X�`���Ȃ����f��
	ObjectBillboard*			pObjectBoard_;					// �r���{�[�h
	ObjectSkinMesh*				pObjectSkinMesh_;				// �X�L�����b�V��
	ObjectRiver*				pObjectRiver_;					// ��

	int							timerLight_;					// ���C�g�p�^�C�}�[

	int							countLight_;					// ���C�g��

	CameraStateSpline*			pCameraState_;					// �J��������
};

#endif	// MY_SCENE_SPLASH_H
